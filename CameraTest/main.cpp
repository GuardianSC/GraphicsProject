#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "Window.h"
#include "Vertex.h"
#include "crenderutils.h"
#include "gallery.h"
#include "Timer.h"
#include "Input.h"
#include "Camera.h"
#include "glObjects.h"

// Welcome to the texture-feature development branch!

int main()
{
	Window window;
	Gallery gallery;
	Time time;
	Input input;
	FlyCamera camera;
	Texture tex;

	// Initializers
	window.init(1350, 750);
	gallery.init();
	time.init();
	input.init(window);

	Vertex verts[] = { { 1,1,0,1 },{ 1,-1,0,1 },{ -1,-1,0,1 },{ -1,1,0,1 } };

	unsigned tris[] = { 0,1,2, 2,3,0 };

	// Loading shader(s)
	gallery.loadShader("TEXTURE", "../res/Shaders/texVert.txt", "../res/Shaders/texFrag.txt");

	// Loading object(s)
	//gallery.loadObjectOBJ("SAMUS", "../res/Models/samus.obj");
	gallery.loadObjectOBJ("SPHERE", "../res/Models/sphere.obj");
	gallery.loadObjectOBJ("CUBE", "../res/Models/cube.obj");

	gallery.makeObject("quad", verts, 4, tris, 6);

	tex = loadTexture("../res/Textures/xray.jpg");
	
	// Current time
	float ct = 0;
	
	// Identity matrix
	float IDENTITY[16] = { 1, 0, 0, 0, // right
						   0, 1, 0, 0, // up
						   0, 0, 1, 0, // forward
						   0, 0, 0, 1 }; // translate

	glm::mat4 projection, view, model;// , model1, model2; // Matrices

	//projection = glm::ortho<float>(-20, 20, -20, 20, -1000, 1000);
	projection = glm::perspective(45.f, 1.f, .1f, 50.f);
	view = glm::lookAt(glm::vec3(10.f, 0.f, 0.f),
		glm::vec3(0, 0, 0.0f),
		glm::vec3(0, 1, 0.f));
	model = glm::translate(glm::vec3(0, 0, 0));//  *glm::rotate(180.f, glm::vec3(0, -1, 0));

	camera.jumpTo(glm::vec3(10, 0, 0));
	camera.lookAt(glm::vec3(0, 0, 0));

	// Game Loop
	while (window.update())
	{
		// update systems
		time.update();
		input.update();
		ct += time.getDeltaTime();

		model = glm::translate(glm::vec3(0, 0, 0)) * glm::rotate(ct  * 10, glm::vec3(0, 1, 0));

		//camera.update(input, time);
		//view = camera.getView();
		//projection = camera.getProjection();

		//fprintf(stdout, "%f\n", ct);

		draw(gallery.getShader("TEXTURE"), gallery.getObject("SPHERE"), tex, glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model), ct);
		//draw(gallery.getShader("TEXTURE"), gallery.getObject("SPHERE"), tex, glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model), ct);

		//draw(gallery.getShader("CAMERA"), gallery.getObject("quad"), glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model), ct);
	}
	// Terminators
	input.term();
	time.term();
	gallery.term();
	window.term();

	return 0;
}