#pragma once

struct Geometry
{
	unsigned vbo, ibo, vao, size;
	// Vertex Buffer Object : an array of vertices
	// Index Buffer Object : an array of indices (triangles)
	// Vertex array Object : groups the two above with some formatting
};

// (forward declaring Vertex instead of using #include "Vertex.h", vertex size, number of tris, size of tris)
Geometry makeGeometry(const struct Vertex *verts, size_t vsize, const unsigned int *tris, size_t tsize); 

void freeGeometry(Geometry &);

struct Shader
{
	unsigned handle;
};

Shader makeShader(const char *vsource, const char *fsource);

Shader loadShader(const char *vpath, const char *fpath);

Geometry loadOBJ(const char *path);

void freeShader(Shader &shader);

void draw(const Shader &shader, const Geometry &geometry);

void draw(const Shader &, const Geometry &, float time);