#pragma once
#include "glObjects.h"

// (Below: forward declaring Vertex instead of using #include "Vertex.h", vertex size, number of tris, size of tris)
Geometry makeGeometry(const struct Vertex *verts, size_t vsize, const unsigned int *tris, size_t tsize);

// Make a custom shader
Shader makeShader(const char *vsource, const char *fsource);

// Make a texture
Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels);
Texture makeTextureF(unsigned square, const float *pixels);

// Make a frame buffer
frameBuffer makeFrameBuffer(unsigned width, unsigned height, unsigned nColors);