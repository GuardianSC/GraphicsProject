#define GLEW_STATIC
#define TINYOBJLOADER_IMPLEMENTATION
#include "GLEW\glew.h"
#include "OBJ\tiny_obj_loader.h"
#include "crenderutils.h"
#include "Vertex.h"
#include <fstream>
#include <string>
#include <iostream>
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

char* getStringFromFile(const char* path) {

	int array_size = 5012;
	char * array = new char[array_size];
	int position = 0;

	std::fstream fin(path);

	if (fin.is_open()) {
#ifdef _DEBUG
		std::string successfulMessage = "Opened the file at ";
		std::cout << successfulMessage.append(path) << std::endl;
#endif
		while (!fin.eof() && position < array_size) {
			fin.get(array[position]);
			position++;
		}
		array[position - 1] = '\0';

#ifdef _DEBUG
		for (int i = 0; array[i] != '\0'; i++)
			std::cout << array[i];
#endif
	}
	else {
		std::cout << "File was not opened";
		return nullptr;
	}

	return array;
}

std::string getTextFromFile(const char *path)
{
	/*std::ifstream file;
	std::string fileContent[100];
	file.open(fileName, std::ios_base::in | std::ios_base::_Nocreate);
	
	if (file.is_open())
		for (int i = 0; i < 5; i++)
			file >> fileContent[i];

	file.close();

	return fileContent[100];*/

	std::ifstream file{ "file.txt" };
	std::string fileContents{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };

	return fileContents;
}

Shader loadShader(const char *vpath, const char *fpath) 
{
	char* v = getStringFromFile(vpath);
	char* f = getStringFromFile(fpath);
	return makeShader(v, f);
}

Geometry loadOBJ(const char *path)
{
	// Use tiny obj to load the file, 
	//extract vertex positions/face data,
	// create an array to store those postions and data
	
	// tiny obj stuff (required to work)
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	// our data stuff
	Vertex * verts = new Vertex[attrib.vertices.size() / 3];
	unsigned * tris = new unsigned[shapes[0].mesh.indices.size()];
	shapes[0].mesh.indices;

	for (int i = 0; i < attrib.vertices.size() / 3; ++i)
	{
		verts[i] = { attrib.vertices[i * 3], 
					 attrib.vertices[i * 3 + 1], 
					 attrib.vertices[i * 3 + 2], 
					 1 };
	}

	for (int i = 0; i < shapes[0].mesh.indices.size() / 3; ++i) {
		tris[i] = shapes[0].mesh.indices[i].vertex_index;
	}
	Geometry retval = makeGeometry(verts, attrib.vertices.size() / 3, tris, shapes[0].mesh.indices.size());

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
	// IF IBO IS BOUND, indices don't need to be provided
	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}

void draw(const Shader &shader, const Geometry &geometry, float time)
{
	glUseProgram(shader.handle);

	glBindVertexArray(geometry.vao);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	int loc = glGetUniformLocation(shader.handle, "time");

	glUniform1f(loc, time);

	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}

void draw(const Shader &shader, const Geometry &geometry, const float P[16], const float M[16], const float  V[16]) // M = Model, V = View, P = Projection
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.handle);

	glBindVertexArray(geometry.vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, M);
	glUniformMatrix4fv(2, 1, GL_FALSE, V);

	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}