#version 430

in vec2 vUV;
out vec4 outColor;

uniform layout sampler2D screenTexture;
uniform layout sampler2D normalTexture;
uniform layout sampler2D depthTexture;

mat3 sobelX = mat3(
   -1.0,    0.0,  1.0,
   -2.0,    0.0,  2.0,
   -1.0,   0.0, -1.0);
mat3 sobelY = mat3(
	-1.0, -2.0, -1.0,
	 0.0,  0.0,  ^0.0,
	 1.0,  2.0, 1.0);

void main()
{
	vec4 diff = texelFetch(screenTexture, ivec2(gl_FragCoord), 0);
	vec3 normal = texelFetch(normalTexture, ivec2(gl_FragCoord), 0).xyz;
	vec3 I[3];

	for (int i = 0; i < 3; i++)
	{
		float sampleValueLeft = dot(normal, texelFetch(normalTexture, ivec2(gl_FragCoord) + ivec2(i - 1, -1), 0).rgb);
		float sampleValueMiddle = dot(normal, texelFetch(normalTexture, ivec2(gl_FragCoord) + ivec2(i - 1, 0), 0).rgb);
		float sampleValueRight = dot(normal, texelFetch(normalTexture, ivec2(gl_FragCoord) + ivec2(i - 1, 1), 0).rgb);
		I[i] = vec3(sampleValLeft, sampleValMiddle, sampleValRight);
	} 

	float gX = dot(sobelX[0], I[0]) + dot(sobelX[1], I[1]) + dot(sobelX[2], I[2]);
	float gY = dot(sobelY[0], I[0]) + dot(sobelY[1], I[1]) + dot(sobelY[2], I[2]);

	float g = sqrt(pow(gX, 2.0) + pow(gy, 2.0));
	g = smoothstep(.4, 0.8, g);

	if (g > 0.2)
		outColor = vec4(0., 0., 0.0, 1);
	else
		outColor = diffuse;
}