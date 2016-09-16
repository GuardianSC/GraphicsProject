#version 430

in vec2 UV;
layout(location = 0)uniform mat4 proj;
layout(location = 1)uniform mat4 view;
layout(location = 2)uniform mat4 model;

layout(location = 3)uniform sampler2D colorMap;		// combined diffuse + specular
layout(location = 4)uniform sampler2D diffuseColor;	// Diffuse
layout(location = 5)uniform sampler2D specularColor; // specular
out vec4 outColor;

uniform vec2 sDim = vec2(1280,720);

void main()
{ 
	vec4 yColor = 
	texture(specularColor,UV + vec2( 1, -1)/sDim)   +
	texture(specularColor,UV + vec2( 0, -1)/sDim)*2 +
	texture(specularColor,UV + vec2(-1, -1)/sDim)   -
	texture(specularColor,UV + vec2( 1,  1)/sDim)    -
	texture(specularColor,UV + vec2( 0,  1)/sDim)*2  -
	texture(specularColor,UV + vec2(-1,  1)/sDim);

	vec4 xColor = 
	texture(specularColor,UV + vec2(-1, -1)/sDim)   +
	texture(specularColor,UV + vec2(-1,  0)/sDim)*2 +
	texture(specularColor,UV + vec2(-1,  1)/sDim)   -
	texture(specularColor,UV + vec2( 1, -1)/sDim)   -
	texture(specularColor,UV + vec2( 1,  0)/sDim)*2 -
	texture(specularColor,UV + vec2( 1,  1)/sDim);

	vec4 yColor1 = 
	texture(specularColor,UV + vec2( 1, -1)/sDim)   +
	texture(specularColor,UV + vec2( 0, -1)/sDim)*2 +
	texture(specularColor,UV + vec2(-1, -1)/sDim)   -
	texture(specularColor,UV + vec2( 1,  1)/sDim)    -
	texture(specularColor,UV + vec2( 0,  1)/sDim)*2  -
	texture(specularColor,UV + vec2(-1,  1)/sDim);

	vec4 xColor1 = 
	texture(diffuseColor,UV + vec2(-1, -1)/sDim)   +
	texture(diffuseColor,UV + vec2(-1,  0)/sDim)*2 +
	texture(diffuseColor,UV + vec2(-1,  1)/sDim)   -
	texture(diffuseColor,UV + vec2( 1, -1)/sDim)   -
	texture(diffuseColor,UV + vec2( 1,  0)/sDim)*2 -
	texture(diffuseColor,UV + vec2( 1,  1)/sDim);

	outColor = sqrt(yColor * yColor + xColor * xColor) + sqrt(xColor1 * xColor1 + yColor1*yColor1);
}
