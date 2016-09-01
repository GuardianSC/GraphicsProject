#include "Window.h"
#include "Vertex.h"
#include "crenderutils.h"
#include "gallery.h"

// Welcome to the file-feature development branch!

int main()
{
	Window window;
	Gallery gallery;

	window.init(600, 600);
	gallery.init();

	/* clip space coordinates, go from -1, 1
	//Vertex vert[6] = { 
	//	// First, larger triangle
	//	{ 0,     .5f, 0, 1, 1, 0, 0, 1 },
	//	{ .5f,  -.5f, 0, 1, 0, 1, 0, 1 },
	//    { -.5f, -.5f, 0, 1, 0, 1, 1, 1 },
	//	// Smaller, second triangle
	//	{ 0,    -.25f, 0, 1, 1, 1, 1, 1 },
	//	{ -.25f, .25f, 0, 1, 0, 1, 0, 1 },
	//	{ .25f,  .25f, 0, 1, 0, 0, 0, 1 },
	//};

	//unsigned tris[6] = { 0, 1, 2, 3, 4, 5 };

	/*const char vsource[] = 
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

	//Geometry geometry1 = makeGeometry(vert, 6, tris, 6);
	//Shader shader1 = makeShader(vsource, fsource);

	//Shader shader = loadShader("../res/Shaders/simpleVert.txt", "../res/Shaders/simpleFrag.txt");

	Geometry geometry = loadOBJ("../res/Models/sphere.obj");*/
	
	gallery.loadShader("SHADER", "../res/shaders/simpleVert.txt", "../res/shaders/simpleFrag.txt");

	//gallery.loadObjectOBJ("SPHERE", "../res/models/sphere.obj");
	//gallery.loadObjectOBJ("PANDA", "../res/models/Panda 1.obj");
	gallery.loadObjectOBJ("CUBE", "../res/models/cube.obj");

	float time = 0;

	while (window.update())
	{
		time += 0.1667f;
		//draw(gallery.getShader("SHADER"), gallery.getObject("SPHERE"), time);
		//draw(gallery.getShader("SHADER"), gallery.getObject("PANDA"), time);
		draw(gallery.getShader("SHADER"), gallery.getObject("CUBE"), time);
	}
	gallery.term();
	window.term();
	return 0;
}