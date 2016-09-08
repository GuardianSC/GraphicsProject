#pragma once
#include "GLM\glm.hpp"
// Stuff for the shader
struct Vertex
{
	//float pos[4];
	//float col[4];

	glm::vec4 position;
	glm::vec4 color;
	glm::vec4 normal;
	glm::vec2 texCoord; // texture coordinate

	enum
	{
		POSITION = 0,
		COLOR = 16,
		NORMAL = 32,
		TEXCOORD = 48
	};
};