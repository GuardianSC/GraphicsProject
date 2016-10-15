#version 430

layout(location = 0) out vec4 position;
layout(location = 1) uniform float time;

out vec2 direction[8];
out vec3 wNormal; // World normal
out vec3 camNormal; // Camera normal

const float pi = 3.14159;
float numWaves;
float time;
float waterHeight;
float amp;
float wLength[8]; // Wave length
float speed[8];

float wave(int i, float x, float y)
{
	float freq = 2 * pi / wavelength[i];
	float phase = speed[i] * freq;
	float theta = dot(direction[i], vec2(x, y));

	return amp[i] * sin(theta * freq + time * phase);
}

float waveHeight(float x, float y)
{
	float height = 0.0;
	for (int i = 0; i < numWaves; ++i)
		height += wave(i, x, y);
	return height;
}

float wavedx(int i, float x, float y)
{
	float freq = 2 * pi / wavelength[i];
	float phase = speed[i] * freq;
	float theta = dot(direction[i], vec2(x, y));
	float A = amp[i] * direction[i].x * freq;
	
	return A * cos(theta * freq + time * phase);
}

float wavedy(int i, float x, float y)
{
	float freq = 2 * pi / wavelength[i];
	float phase = speed[i] * freq;
	float theta = dot(direction[i], vec2(x, y));
	float A = amp[i] * direction[i].y * freq;

	return A * cos(theta * freq + time * phase);
}

vec3 waveNormal(float x, float y)
{
	float dx = 0.0;
	float dy = 0.0;

	for (int i = 0; i < numWaves; ++i)
	{
		dx += wavedx(i, x, y);
		dy += wavedy(i, x, y);
	}

	vec3 N = vec3(-dx, -dy, 1.0);
	return normalize(n);
}

void main()
{
	vec4 pos = gl_Vertex;
	pos.z = waterHeight + waveHeight(pos.x, pos.y);
	position = pos.xyz / pos.w;
	wNormal = waveNormal(pos.x, pos.y);
	camNormal = gl_NormalMatrix * wNormal;
	gl_Position = gl_ModelViewProjectionMatrix * pos;
}