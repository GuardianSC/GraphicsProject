#include "Window.h"
#include "Vertex.h"
#include "crenderutils.h"

// Welcome to the development (context-feature) branch!

int main()
{
	Window window;
	window.init();

	Vertex vert[3] = { {.5, .5, 0,  1},
					   { .5, 0, .5,  1},
					   {-.5, .5, -.5, 1} };
	unsigned tris[3] = { 0, 1, 2 };

	const char vsource[] = "#version 150\n"
							"in vec4 position;"
							"void main() {gl_Position = position;}";

	const char fsource[] = "#version 150\n"
							"out vec4 outColor;"
							"void main() {outColor = vec4(1.0, 0.0, 0.0, 1.0);}";

	Geometry geometry = makeGeometry(vert, 3, tris, 3);
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