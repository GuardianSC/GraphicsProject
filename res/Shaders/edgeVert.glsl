#version 430

layout(location = 0) in vec3 position;
layout(location = 3) in vec3 texCoord;

out vec2 vUV;

void main()
{
	vUV = texCoord;
	gl_Position = position;
}