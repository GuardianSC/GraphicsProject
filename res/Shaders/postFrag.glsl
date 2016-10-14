#version 430

in vec2 UV;
layout(location = 0)uniform mat4 proj;
layout(location = 1)uniform mat4 view;
layout(location = 2)uniform mat4 model;

layout(location = 3)uniform sampler2D colorMap;		// combined diffuse + specular
layout(location = 4)uniform sampler2D depth;

out vec4 outColor;

uniform vec2 sDim = vec2(1280, 720); // screen dimension

void main()
{
	vec4 yColor =
		texture(colorMap, UV + vec2(1, -1) / sDim) +
		texture(colorMap, UV + vec2(0, -1) / sDim) * 2 +
		texture(colorMap, UV + vec2(-1, -1) / sDim) -
		texture(colorMap, UV + vec2(1, 1) / sDim) -
		texture(colorMap, UV + vec2(0, 1) / sDim) * 2 -
		texture(colorMap, UV + vec2(-1, 1) / sDim);

	vec4 xColor =
		texture(colorMap, UV + vec2(-1, -1) / sDim) +
		texture(colorMap, UV + vec2(-1, 0) / sDim) * 2 +
		texture(colorMap, UV + vec2(-1, 1) / sDim) -
		texture(colorMap, UV + vec2(1, -1) / sDim) -
		texture(colorMap, UV + vec2(1, 0) / sDim) * 2 -
		texture(colorMap, UV + vec2(1, 1) / sDim);

	outColor = sqrt(yColor * yColor + xColor * xColor);
}