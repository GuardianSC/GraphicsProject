// Bloom
#version 430

layout(location = 0) uniform sampler2D renderGeo;
layout(location = 2) uniform sampler2D lightAlbedo;

in vec2 vUV;
in float deltaTime;

out vec4 outColor;

vec4 sum = vec4(0);
vec4 white = vec4(1, 1, 1, 1);

void main()
{
	vec4 threshold = vec4(0.5, 0.5, 0.5, 0.5);
	vec4 albedo = texture(renderGeo, vUV);
	vec4 lAlbedo = texture(lightAlbedo, vUV); // Vec4 light albedo

	// -2 to 2 are the 5 pixels we are sampling (0 is origin pixel)
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			vec2 offset = vec2(i, j) * 0.005;
			sum += texture2D(renderGeo, vUV + offset);
		}
	}

	if (length(albedo) > length(threshold))
		outColor = vec4(0, 1, 1, 1);
	else
		outColor = ((sum / 25) + (albedo + lAlbedo));
}