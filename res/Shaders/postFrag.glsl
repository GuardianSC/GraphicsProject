#version 430

in vec2 vUV;
out vec4 outColor;

layout(location = 0) uniform mat4 proj;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 model;

layout(location = 3) uniform sampler2D map;
layout(location = 4) uniform sampler2D depth;

vec4 sobel(in sampler2D map, in vec2 UV);

vec2 sDim = vec2(1350, 750);

void main()
{
	outColor = sobel(map, vUV);
}

vec4 sobel(in sampler2D map, in vec2 UV)
{
	vec4 yColor =
		texture(map, UV + vec2(1, -1)  / sDim) +
		texture(map, UV + vec2(0, -1)  / sDim) * 2 +
		texture(map, UV + vec2(-1, -1) / sDim) -
		texture(map, UV + vec2(1, 1)   / sDim) -
		texture(map, UV + vec2(0, 1)   / sDim) * 2 -
		texture(map, UV + vec2(-1, 1)  / sDim);

	vec4 xColor =
		texture(map, UV + vec2(-1, -1) / sDim) +
		texture(map, UV + vec2(-1, 0)  / sDim) * 2 +
		texture(map, UV + vec2(-1, 1)  / sDim) -
		texture(map, UV + vec2(1, -1)  / sDim) -
		texture(map, UV + vec2(1, 0)   / sDim) * 2 -
		texture(map, UV + vec2(1, 1)   / sDim);

	return sqrt(yColor * yColor + xColor * xColor);
}