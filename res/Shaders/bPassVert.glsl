// Bloom
#version 430

layout(location = 0) in vec4 position;
layout(location = 3) in vec2 texCoord;
layout(location = 0) uniform sampler2D renderGeo;
layout(location = 1) uniform float time;

out vec2 vUV;
out float deltaTime;

void main()
{
	vUV = texCoord;
	deltaTime = time;
	gl_Position = position;
}