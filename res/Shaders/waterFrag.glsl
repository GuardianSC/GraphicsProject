#version 430

layout(location = 0) uniform sampler2D waterMap;

in vec3 position;
in vec3 wNormal;
in vec3 camNormal;
vec3 camPos;

void main()
{
	vec3 cam = normalize(camPos - position);
	vec3 r = reflect(cam, wNormal);
	vec4 color = texture2D(waterMap, r);
	color.a = 0.5;
	gl_FragColor = color;
}