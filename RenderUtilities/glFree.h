#pragma once
#include "glObjects.h"

// Free (unload) goemetry
void freeGeometry(Geometry &);

// Free (unload) shaders
void freeShader(Shader &shader);

// Free (unload) textures
void freeTexture(Texture &texture);

void freeFrameBuffer(frameBuffer &fb);
void clearFrameBuffer(frameBuffer &fb);