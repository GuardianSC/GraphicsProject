#define GLEW_STATIC
#include "GLEW\glew.h"
#include "glFree.h"

void freeGeometry(Geometry &geo)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);
	geo = { 0, 0, 0, 0 };
}

void freeShader(Shader &shader)
{
	glDeleteProgram(shader.handle);
	shader.handle = 0;
}

void freeTexture(Texture &texture)
{
	glDeleteTextures(1, &texture.handle);
	texture = { 0, 0, 0, 0 };
}

void freeFrameBuffer(FrameBuffer &fb)
{
	for (unsigned i = 0; i < fb.nColors; i++)
		freeTexture(fb.colors[i]);

	glDeleteFramebuffers(1, &fb.handle);
	fb = { 0, 0, 0, 0 };
}

void clearFrameBuffer(FrameBuffer &fb)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fb.handle);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}