#version 430

layout(location = 0) in vec4 position;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec2 texCoord;
// UVs and Normals later.


layout(location = 0)uniform mat4 projection;
layout(location = 1)uniform mat4 view;
layout(location = 2)uniform mat4 model;

out vec4 vNormal;
out vec4 vPosition;
out vec2 UV;

void main()
{
	vNormal = model * normal;
	UV = texCoord;
	vPosition = model * position;

	gl_Position = projection * view * model * position;
}