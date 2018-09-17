#pragma once
#include "GLM\ext.hpp"
//#include <gl\GL.h>
#include "GLEW\glew.h"
struct Geometry
{
	// Vertex Buffer Object : an array of vertices
	// Index Buffer Object  : an array of indices (triangles)
	// Vertex array Object  : groups the two above with some formatting
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

struct Particle
{
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec4 color;
	
	GLfloat life;

	Particle() : position(0.0f), velocity(0.0f), color(1.0f), life(0.0f) { }
};

struct FrameBuffer
{
	unsigned handle;
	unsigned width, height, nColors;
	Texture depth, colors[8];
};