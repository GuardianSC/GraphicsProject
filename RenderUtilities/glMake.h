#pragma once
#include "glObjects.h"

// (Below: forward declaring Vertex instead of using #include "Vertex.h", vertex size, number of tris, size of tris)
struct Geometry makeGeometry(const struct Vertex *verts, size_t vsize, const unsigned int *tris, size_t tsize);

// Make a custom shader
struct Shader makeShader(const char *vsource, const char *fsource, bool depth = true, bool add = false, bool face = true);

// Make a texture
struct Texture makeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char *pixels);
struct Texture makeTextureF(unsigned square, const float *pixels);

// Make a frame buffer
struct frameBuffer makeFrameBuffer(unsigned width, unsigned height, unsigned nColors);