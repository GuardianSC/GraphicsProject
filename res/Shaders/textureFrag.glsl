#version 430

in  vec2  vtexCoord;
out vec4  outColor;

layout(location = 4) uniform sampler2D texMap;
layo

void main ()
{ 
	outColor = texture(texMap, vtexCoord).rrrr;
}