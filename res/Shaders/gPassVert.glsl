#version 430

layout(location = 0) in vec4 position;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec2 texCoord;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

out vec2 vUV;
out vec3 vNormal;
out vec3 vPosition;


void main()
{
	vNormal = (view * model * normal).xyz;
	vPosition = (view * model * position).xyz;
	vUV = texCoord;
	gl_Position = projection * view * model * position;
}