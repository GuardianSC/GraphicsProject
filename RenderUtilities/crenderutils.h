#pragma once

struct Geometry
{
	unsigned vbo, ibo, vao, size;
	// Vertex Buffer Object : an array of vertices
	// Index Buffer Object : an array of indices (triangles)
	// Vertex array Object : groups the two above with some formatting
};

// (forward declaring Vertex instead of using #include "Vertex.h", vertex size, number of tris, size of tris)
Geometry makeGeometry(struct Vertex *verts, size_t vsize, unsigned int *tris, size_t tsize); 

void freeGeometry(Geometry &);