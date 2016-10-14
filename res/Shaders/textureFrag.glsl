#version 430

in  vec2  vTexCoord;
out vec4  outColor;

layout(location = 4) uniform sampler2D texMap;

void main ()
{ 
	outColor = texture(texMap, vTexCoord).rrrr;
}