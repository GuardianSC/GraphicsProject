#pragma once
#include <string>
#include <map>
#include "crenderutils.h"

class Gallery
{
	std::map<std::string, Geometry> geometries;
	std::map<std::string, Shader>	shaders;
	std::map<std::string, Texture>  textures;

public:
	// Make a custom shader
	bool makeShader(const char *name, const char *vsource, const char *fsource);
	// Load a shader
	bool loadShader(const char *name, const char *vpath, const char *fpath);
	// Make a texture
	bool makeTexture(const char *name, int w, int h, int f, const unsigned char *p);
	// Load a texture
	bool loadTexture(const char *name, const char *path);
	// Make a custom object
	bool makeObject(const char *name, const Vertex *verts, size_t vsize,
		const unsigned *tris, size_t tsize);
	// Load existing object
	bool loadObjectOBJ(const char *name, const char *path);
	// Get an object
	const Geometry &getObject(const char *name);
	// Get a shader
	const Shader &getShader(const char *name);
	// Get texture
	const Texture &Gallery::getTexture(const char * name);
	// Initialize
	bool init();
	// Terminate
	bool term();
};