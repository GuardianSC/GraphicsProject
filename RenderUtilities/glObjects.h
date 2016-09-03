#pragma once

struct Geometry
{
	// Vertex Buffer Object : an array of vertices
	// Index Buffer Object : an array of indices (triangles)
	// Vertex array Object : groups the two above with some formatting
	unsigned vbo, ibo, vao, size;
};

struct Shader
{
	unsigned handle;
};

struct Texture
{
	unsigned handle;
	unsigned width, height, format;
};