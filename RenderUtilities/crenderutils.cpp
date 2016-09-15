#define GLEW_STATIC
#define TINYOBJLOADER_IMPLEMENTATION
#include "GLEW\glew.h"
#include "OBJ\tiny_obj_loader.h"
#include "crenderutils.h"
#include "Vertex.h"
#include "glObjects.h"
#define STB_IMAGE_IMPLEMENTATION
#include "STB\stb_image.h"
#include <fstream>
#include <string>
#include <iostream>
#include <random>
#include <cstdio>

Geometry loadOBJ(const char *path)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);
	int vsize = shapes[0].mesh.indices.size();
	Vertex   *verts = new Vertex[vsize];
	unsigned * tris = new unsigned[vsize];

	for (int i = 0; i < vsize; ++i)
	{
		auto ind = shapes[0].mesh.indices[i];

		const float *n = &attrib.normals[ind.normal_index * 3]; // +1, +2, 0
		const float *p = &attrib.vertices[ind.vertex_index * 3]; // +1, +2, 1

		verts[i].position = glm::vec4(p[0], p[1], p[2], 1.f);
		verts[i].normal = glm::vec4(n[0], n[1], n[2], 0.f);

		if (ind.texcoord_index >= 0)
		{
			const float *t = &attrib.texcoords[ind.texcoord_index * 2]; // +1
			verts[i].texCoord = glm::vec2(t[0], t[1]);
		}

		tris[i] = i;
	}

	Geometry retval = makeGeometry(verts, vsize, tris, vsize);

	delete[] verts;
	delete[] tris;
	// then we can call makeGeometry as per normal.
	return retval;
}


Geometry makeGeometry(const Vertex * verts, size_t vsize,
	const unsigned int * tris, size_t tsize)
{
	Geometry retval;

	// Define the variables
	glGenBuffers(1, &retval.vbo);	   // Store vertices
	glGenBuffers(1, &retval.ibo);	   // Store indices
	glGenVertexArrays(1, &retval.vao); // Store attribute information

									   // Scope the variables
	glBindVertexArray(retval.vao);
	glBindBuffer(GL_ARRAY_BUFFER, retval.vbo); // scope our vertices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo); // triangle is scoped

													   // Initialize the variables
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris, GL_STATIC_DRAW);

	// Attributes let us tell openGL how the memory is laid out
	glEnableVertexAttribArray(0); // Position
	glEnableVertexAttribArray(1); // Color
	glEnableVertexAttribArray(2); // Normal
	glEnableVertexAttribArray(3); // TexCoord

								  // index of the attribute, number of elements, type, normalized?, size of vertex, offset
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::COLOR);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::NORMAL);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::TEXCOORD);

	// unscope the variables
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	retval.size = tsize;
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

Shader loadShader(const char *vpath, const char *fpath) 
{
	char* v = getStringFromFile(vpath);
	char* f = getStringFromFile(fpath);
	return makeShader(v, f);
}

void freeShader(Shader &shader)
{
	glDeleteProgram(shader.handle);
	shader.handle = 0;
}

Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels)
{
	Texture retval = { 0, width, height, format };

	glGenTextures(1, &retval.handle);				// Declaration
	glBindTexture(GL_TEXTURE_2D, retval.handle);    // Scoping

	// GL_RED, GL_RG, GL_RGB, GL_RGBA
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	return retval;
}

Texture makeTextureF(unsigned square, const float * pixels)
{
	Texture retval = { 0, square, square, GL_RED };

	glGenTextures(1, &retval.handle);
	glBindTexture(GL_TEXTURE_2D, retval.handle);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, square, square, 0, GL_RED, GL_FLOAT, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);

	return retval;
}

Texture loadTexture(const char *path)
{
	int w, h, f;
	unsigned char *p;

	Texture retval = { 0,0,0,0 };

	stbi_set_flip_vertically_on_load(true); // DirectX or OpenGL
	p = stbi_load(path, &w, &h, &f, STBI_default);

	if (!p) return retval;

	switch (f)
	{
	case STBI_grey: f = GL_RED;  break;
	case STBI_grey_alpha: f = GL_RG;   break;
	case STBI_rgb: f = GL_RGB;  break;
	case STBI_rgb_alpha: f = GL_RGBA; break;
	}

	retval = makeTexture(w, h, f, p);
	stbi_image_free(p);
	return retval;
}

void freeTexture(Texture &texture)
{
	glDeleteTextures(1, &texture.handle);
	texture = { 0, 0, 0, 0 };
}

frameBuffer makeFrameBuffer(unsigned width, unsigned height, unsigned nColors)
{
	// handle, width, height, colors[8]
	frameBuffer retval = { 0, width, height, nColors };

	glGenFramebuffers(1, &retval.handle);
	glBindFramebuffer(GL_FRAMEBUFFER, retval.handle);

	retval.depth = makeTexture(width, height, GL_DEPTH_COMPONENT, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, retval.depth.handle, 0);

	const GLenum attachments[8] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,
								    GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5,
								    GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7 };
	
	// Make/attach textures
	for (int i = 0; i < nColors && i < 8; ++i)
	{
		retval.colors[i] = makeTexture(width, height, GL_RGBA, 0);
		glFramebufferTexture(GL_FRAMEBUFFER, attachments[i], retval.colors[i].handle, 0);
	}

	glDrawBuffers(nColors, attachments);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return retval;
}

void freeFrameBuffer(frameBuffer &fb)
{
	for (unsigned i = 0; i < fb.nColors; i++)
		freeTexture(fb.colors[i]);

	glDeleteFramebuffers(1, &fb.handle);
	fb = { 0, 0, 0, 0 };
}

void clearFrameBuffer(frameBuffer &fb)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fb.handle);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

#pragma region Draw
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

// P = Projection, M = Model, V = View,
void draw(const Shader &shader, const Geometry &geometry, const float P[16], const float V[16], const float  M[16], float time) 
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

void draw(const Shader &shader, const Geometry &geometry, const Texture &texture, const float P[16], const float V[16], const float  M[16], float time) // M = Model, V = View, P = Projection
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.handle);

	glBindVertexArray(geometry.vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);
	
	
	glUniform1f(3, time);

	// Minimum guaranteed is 8
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.handle);
	glUniform1i(4, 0);

	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}

// Lighting calls
void drawPhong(const Shader & shader, const Geometry &geometry, const float P[16], const float V[16], const float M[16])
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.handle);
	glBindVertexArray(geometry.vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);

	// Light Direction
	// Light Color
	// Specular Factor
	// Normal Map
	// Albedo Map (color)

	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}

void drawPhong(const Shader & shader, const Geometry &geometry, const float P[16], const float V[16], const float M[16], const Texture *Texture, unsigned tcount)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.handle);
	glBindVertexArray(geometry.vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);

	// Light Direction
	// Light Color
	// Specular Factor
	// Normal Map
	// Albedo Map (color)

	for (int i = 0; i < tcount; ++i)
	{
		// Minimum guaranteed is 8
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, Texture[i].handle);
		glUniform1i(3 + i, 0 + i);
	}

	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}

void drawFB(const Shader & shader, const Geometry & geometry, const frameBuffer &f, const float P[16], const float V[16], const float M[16], const Texture * Texture, unsigned tcount)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glUseProgram(shader.handle);
	glBindVertexArray(geometry.vao);

	glViewport(0, 0, f.width, f.height);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);

	for (int i = 0; i < tcount; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, Texture[i].handle);
		glUniform1i(3 + i, 0 + i);
	}


	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}
#pragma endregion