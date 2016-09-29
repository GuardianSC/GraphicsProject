#version 430

layout(location = 0) in vec4 position;
layout(location = 3) in vec2 texCoord;

layout(location = 0) uniform mat4 model;

out vec2 vUV;

void main()
{
	vUV = texCoord;
	gl_Position = model * position;
}