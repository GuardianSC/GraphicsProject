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
	bool depthTest;
	bool additiveBlend;
	bool faceCulling;
};

struct Texture
{
	unsigned handle;
	unsigned width, height, format;
};

struct FrameBuffer
{
	unsigned handle;
	unsigned width, height, nColors;
	Texture depth, colors[8];
};