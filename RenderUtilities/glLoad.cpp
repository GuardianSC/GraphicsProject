#define GLEW_STATIC
#include "GLEW\glew.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "OBJ\tiny_obj_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "STB\stb_image.h"
#include "glLoad.h"
#include "glMake.h"
#include "vertex.h"
#include <iostream>

char* getStringFromFile(const char* path) {

	int array_size = 5012;
	char *array = new char[array_size];
	int position = 0;

	std::fstream fin(path);

	if (fin.is_open()) {
#ifdef _DEBUG
		std::string successfulMessage = "Opened the file at ";
		std::cout << successfulMessage.append(path) << std::endl;
#endif
		while (!fin.eof() && position < array_size) {
			fin.get(array[position]);
			position++;
		}
		array[position - 1] = '\0';

#ifdef _DEBUG
		for (int i = 0; array[i] != '\0'; i++)
			std::cout << array[i];
#endif
	}
	else {
		std::cout << "File was not opened";
		return nullptr;
	}

	return array;
}

Geometry loadOBJ(const char *path)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);
	int vsize = shapes[0].mesh.indices.size();
	Vertex   *verts = new Vertex[vsize];
	unsigned * tris = new unsigned[vsize];

	for (int i = 0; i < vsize; ++i)
	{
		auto ind = shapes[0].mesh.indices[i];

		const float *n = &attrib.normals[ind.normal_index * 3]; // +1, +2, 0
		const float *p = &attrib.vertices[ind.vertex_index * 3]; // +1, +2, 1

		verts[i].position = glm::vec4(p[0], p[1], p[2], 1.f);
		verts[i].normal = glm::vec4(n[0], n[1], n[2], 0.f);

		if (ind.texcoord_index >= 0)
		{
			const float *t = &attrib.texcoords[ind.texcoord_index * 2]; // +1
			verts[i].texCoord = glm::vec2(t[0], t[1]);
		}

		tris[i] = i;
	}

	Geometry retval = makeGeometry(verts, vsize, tris, vsize);

	delete[] verts;
	delete[] tris;
	// then we can call makeGeometry as per normal.
	return retval;
}


Shader loadShader(const char *vpath, const char *fpath)
{
	char* v = getStringFromFile(vpath);
	char* f = getStringFromFile(fpath);
	return makeShader(v, f);
}

Texture loadTexture(const char *path)
{
	int w, h, f;
	unsigned char *p;

	Texture retval = { 0,0,0,0 };

	stbi_set_flip_vertically_on_load(true); // DirectX or OpenGL
	p = stbi_load(path, &w, &h, &f, STBI_default);

	if (!p) return retval;

	switch (f)
	{
	case STBI_grey: f = GL_RED;  break;
	case STBI_grey_alpha: f = GL_RG;   break;
	case STBI_rgb: f = GL_RGB;  break;
	case STBI_rgb_alpha: f = GL_RGBA; break;
	}

	retval = makeTexture(w, h, f, p);
	stbi_image_free(p);
	return retval;
}