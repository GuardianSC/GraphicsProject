#version 430

in vec3 wPos;
in vec3 wNormal;

layout(location = 0) out vec4 outColor;

uniform vec3 lPos; // Light pos
uniform vec3 cPos; // Camera pos

uniform int matShine;
uniform float matkd;
uniform float matks;

void main()
{
	vec3 L = normalize(lPos - wPos);
	vec3 V = normalize(cPos - wPos);
	vec3 H = normalize(L + V);

	float diff = matkd * max(0, dot(L, wNormal));
	float spec = 0;

	if (dot(L, wNormal) > 0.0)
	{
		spec = matks * pow(max(0, dot(H, wNormal)), matShine);
	}

	float edgeDetection = (dot(V, wNormal) > 0.3) ? 1 : 0;

	float light = edgeDetection * (diff + spec);
	vec3 color = vec3(light, light, light);

	outColor = vec4(color, 1);
}