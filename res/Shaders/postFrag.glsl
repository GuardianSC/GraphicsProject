#version 430

out vec4 outColor;

in vec2 UV;

layout(location = 0) uniform sampler2D map;
layout(location = 1) uniform sampler2D litMap;

vec4 sobel(in sampler2D map, in vec2 vUV);
vec4 crossblur(in sampler2D map, in vec2 vUV);

void main()
{
	vec4 s = sobel(map, UV);
	vec4 b = crossblur(map, UV);
	if (length(s) > 0.5)
	{
		s = vec4(0, 0, 0, 0);
	}

	outColor = texture(litMap, UV) + s + b;
}

vec4 crossblur(in sampler2D map, in vec2 vUV)
{
	vec2 sDim = textureSize(map, 0).xy;
	vec4 retval = vec4(0, 0, 0, 0);
	for (int i = -9; i <= 9; ++i)
	{
		retval += texture(map, vUV + vec2(i, 0) / sDim);
		retval += texture(map, vUV + vec2(0, i) / sDim);
	}
	return retval / 36;
}

vec4 sobel(in sampler2D map, in vec2 vUV)
{
	vec2 sDim = textureSize(map, 0).xy;
	vec4 threshold = vec4(0.5, 0.5, 0.5, 0.5);

	vec4 yColor =
		texture(map, vUV + vec2(1, -1) / sDim) +
		texture(map, vUV + vec2(0, -1) / sDim) * 2 +
		texture(map, vUV + vec2(-1, -1) / sDim) -
		texture(map, vUV + vec2(1, 1) / sDim) -
		texture(map, vUV + vec2(0, 1) / sDim) * 2 -
		texture(map, vUV + vec2(-1, 1) / sDim);

	vec4 xColor =
		texture(map, vUV + vec2(-1, -1) / sDim) +
		texture(map, vUV + vec2(-1, 0) / sDim) * 2 +
		texture(map, vUV + vec2(-1, 1) / sDim) -
		texture(map, vUV + vec2(1, -1) / sDim) -
		texture(map, vUV + vec2(1, 0) / sDim) * 2 -
		texture(map, vUV + vec2(1, 1) / sDim);

	// -2 to 2 are the 5 pixels we are sampling (0 is origin pixel)
	//for (int i = -2; i <= 2; i++)
	//{
	//	for (int j = -2; j <= 2; j++)
	//	{
	//		vec2 offset = vec2(i, j) * 0.005;
	//		sum += texture2D(map, vUV + offset);
	//	}
	//}

	//if ()

	return sqrt(yColor * yColor + xColor * xColor);
}