#version 430

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

// world pos, normal
out vec3 wPos;
out vec3 wNormal;

void main()
{
	wPos = mat3(model) * position;
	wNormal = normalize(mat3(model) * normal);
	gl_Position = projection * view * model * vec4(position, 1);
}