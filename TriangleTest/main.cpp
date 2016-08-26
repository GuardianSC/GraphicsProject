#include "Window.h"
#include "Vertex.h"
#include "crenderutils.h"

// Welcome to the main development branch!

int main()
{
	Window window;
	window.init();

	Vertex vert[6] = { 
		{ 0,  .5f, 0, 1, 1, 0, 0, 1 },
		{ .5f, -.5f, 0, 1, 0, 1, 0, 1 },
	    { -.5f, -.5f, 0, 1, 0, 1, 1, 1 },

		{ 0,  -.5f, 0, 1, 1, 0, 0, 1 },
		{ -.5f, .5f, 0, 1, 0, 1, 0, 1 },
		{ .5f, .5f, 0, 1, 0, 1, 1, 1 },
	};

	unsigned tris[6] = { 0, 1, 2, 3, 4, 5 };

	const char vsource[] = 
		"#version 330\n"
		"layout(location = 0)in vec4 position;"
		"layout(location = 1)in vec4 color;"
		"out vec4 vColor;"
		"void main() { vColor = color; gl_Position = position; } ";

	const char fsource[] = 
		"#version 150\n"
		"in vec4 vColor;"
		"out vec4 outColor;"
		"void main () { outColor = vColor; } ";

	Geometry geometry = makeGeometry(vert, 6, tris, 6);
	Shader shader = makeShader(vsource, fsource);
	
	while (window.step())
	{
		draw(shader, geometry);
	}
	freeGeometry(geometry);
	freeShader(shader);
	window.term();
	return 0;
}