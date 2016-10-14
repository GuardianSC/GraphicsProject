#version 430

out vec4 outColor;

in vec2 vUV;

uniform sampler2D renderTex;

void main()
{
	vec4 color = texture2D(renderTex, gl_TexCoord[0]);
	for (int i = -2; i <= 2; i++)
		for (int j = -2; j <= 2; j++)
		{
			vec2 offset = vec2(i, j) * 0.005;
			sum += texture2D(renderTex, gl_TexCoord[0] + offset);
		}
	outColor = (sum / 25) + color;
}