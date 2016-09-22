#pragma once
#include "glObjects.h"

// Load an existing object
struct Geometry loadOBJ(const char *path);

// Make a custom shader
//Shader makeShader(const char *vsource, const char *fsource);
// Load a custom shader
struct Shader loadShader(const char *vpath, const char *fpath, bool depth = true, bool add = false, bool face = true);

// Load a texture
struct Texture loadTexture(const char *path);