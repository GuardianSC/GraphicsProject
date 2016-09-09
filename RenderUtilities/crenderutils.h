#pragma once
#include "glObjects.h"

// Load an existing object
Geometry loadOBJ(const char *path);

// (Below: forward declaring Vertex instead of using #include "Vertex.h", vertex size, number of tris, size of tris)
Geometry makeGeometry(const struct Vertex *verts, size_t vsize, const unsigned int *tris, size_t tsize); 
// Free (unload) geometric objects
void freeGeometry(Geometry &);

// Make a custom shader
Shader makeShader(const char *vsource, const char *fsource);
// Load a custom shader
Shader loadShader(const char *vpath, const char *fpath);

// Free (unload) shaders
void freeShader(Shader &shader);

Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels);
Texture makeTextureF(unsigned square, const float *pixels);
Texture loadTexture(const char *path);

void freeTexture(Texture &texture);

// Different draw functions
void draw(const Shader &shader, const Geometry &geometry);

void draw(const Shader &shader, const Geometry &geometry, float time);

// @TODO: chris pls add details
// P = Projection, V = View, M = Model
void draw(const Shader &shader, const Geometry &geometry, const float P[16], const float V[16], const float  M[16], float time); 

// Texture Draw
void draw(const Shader &shader, const Geometry &geometry, const class Texture &texture, const float P[16], const float V[16], const float  M[16], float time);
// Color depth -- 24-bit colors vs 32-bit colors vs 8-bit colors

void drawPhong(const Shader &shader, const Geometry &geometry, const float P[16], const float V[16], const float M[16]);

void drawPhong(const Shader & shader, const Geometry & geometry, const float P[16], const float V[16], const float M[16], const Texture *T, unsigned tcount);