#pragma once
#include "glObjects.h"

// Generate a grid (square (sqr) is size of texture, dim is dimensions of grid)
Geometry genGrid(unsigned sqr, float dim);

// Generate some "noise" on a texture (square (sqr) is size of texture)
Texture genNoise(unsigned sqr, unsigned octaves);