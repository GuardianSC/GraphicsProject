#version 430

layout(location = 0) in vec4 position;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec2 texCoord;

layout(location = 0)uniform mat4 projection;
layout(location = 1)uniform mat4 view;
layout(location = 2)uniform mat4 model;

out vec3 vPosition;
out vec3 vNormal;
out vec2 UV;

void main()
{
	vNormal = (model * normal).xyz;
	UV = texCoord;
	vPosition = normalize(model * position).xyz;

	gl_Position = projection * view * model * position;
}