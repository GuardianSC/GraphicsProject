#pragma once
#include "glObjects.h"

// Generate a grid (square (sqr) is size of texture, dim is dimensions of grid)
Geometry GenGrid(unsigned sqr, float dim);

// Generate some "noise" on a texture (square (sqr) is size of texture)
Texture GenNoise(unsigned sqr, unsigned octaves);