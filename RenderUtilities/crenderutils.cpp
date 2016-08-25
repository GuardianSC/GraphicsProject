#define GLEW_STATIC
#include "GLEW\glew.h"
#include "crenderutils.h"
#include "Vertex.h"

Geometry makeGeometry(const Vertex * verts, const size_t vsize, const unsigned int * tris, size_t tsize)
{
	Geometry retval;
	retval.size = tsize;
	// Define, manually scope, initialize, and then unscope the variables

	// Define
	glGenBuffers(1, &retval.vbo); // store vertices
	glGenBuffers(1, &retval.ibo); // store indices
	glGenVertexArrays(1, &retval.vao); // store attribute information (inside the vertex struct)

	// Scope
	glBindVertexArray(retval.vao); // binds the only active buffer (only one buffer can be active at a time)
	glBindBuffer(GL_ARRAY_BUFFER, retval.vbo); // scope vertices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo); // // scope triangle
	
	// Initialize
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris, GL_STATIC_DRAW);

	// Attributes
	glEnableVertexAttribArray(0); // position
	glEnableVertexAttribArray(1); // color

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION); // position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::COLOR); // color
	// Unscope
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return retval;
}

void freeGeometry(Geometry &geo)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);
	geo = { 0, 0, 0, 0 };
}

Shader makeShader(const char *vsource, const char *fsource)
{
	Shader retval;
	// create variables
	retval.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);
	// initialize variables
	glShaderSource(vs, 1, &vsource, 0);
	glShaderSource(fs, 1, &fsource, 0);
	// compile shaders
	glCompileShader(vs);
	glCompileShader(fs);
	// link shaders to a  single program
	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);
	glLinkProgram(retval.handle);
	// delete shaders
	glDeleteShader(vs);
	glDeleteShader(fs);

	return retval;
}

void freeShader(Shader &shader)
{
	glDeleteProgram(shader.handle);
	shader.handle = 0;
}

void draw(const Shader &shader, const Geometry &geometry)
{
	glUseProgram(shader.handle);
	// binding VAO also binds IBO(tri) and VBO (verts)
	glBindVertexArray(geometry.vao);
	// draw elements will draw vertices that are currently bound using an array of indices.
	// IF IBO IS BOUND, indices don't need ot be provided
	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}