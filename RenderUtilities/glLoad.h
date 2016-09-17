#pragma once
#include "glObjects.h"

// Load an existing object
Geometry loadOBJ(const char *path);

// Make a custom shader
//Shader makeShader(const char *vsource, const char *fsource);
// Load a custom shader
Shader loadShader(const char *vpath, const char *fpath);

// Load a texture
Texture loadTexture(const char *path);