#pragma once

struct Geometry
{
	unsigned vbo, ibo, vao, size;
	// Vertex Buffer Object : an array of vertices
	// Index Buffer Object : an array of indices (triangles)
	// Vertex array Object : groups the two above with some formatting
};

// (Below: forward declaring Vertex instead of using #include "Vertex.h", vertex size, number of tris, size of tris)
Geometry makeGeometry(const struct Vertex *verts, size_t vsize, const unsigned int *tris, size_t tsize); 
// Free (unload) geometric objects
void freeGeometry(Geometry &);

struct Shader
{
	unsigned handle;
};
// Make a custom shader
Shader makeShader(const char *vsource, const char *fsource);
// Load a custom shader
Shader loadShader(const char *vpath, const char *fpath);
// Load an existing object
Geometry loadOBJ(const char *path);
// Free (unload) shaders
void freeShader(Shader &shader);

// Different draw functions
void draw(const Shader &shader, const Geometry &geometry);

void draw(const Shader &shader, const Geometry &geometry, float time);

void draw(const Shader &shader, const Geometry &geometry, const float M[16], const float V[16], const float  P[16]); // M = Model, V = View, P = Projection