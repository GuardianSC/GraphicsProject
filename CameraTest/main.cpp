#include "Window.h"
#include "Vertex.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"
#include "crenderutils.h"
#include "gallery.h"
#include "Timer.h"
#include "Input.h"
#include "Camera.h"

// Welcome to the camera-feature development branch!

int main()
{
	Window window;
	Gallery gallery;
	Time time;
	Input input;
	FlyCamera camera;

	// Initializers
	window.init(1350, 750);
	gallery.init();
	time.init();
	input.init(window);

	// Loading shader
	gallery.loadShader("CAMERA", "../res/shaders/cameraVert.txt", "../res/shaders/cameraFrag.txt");
	// Loading objects
	gallery.loadObjectOBJ("SAMUS", "../res/models/samus.obj");
	gallery.loadObjectOBJ("SPHERE", "../res/models/sphere.obj");
	gallery.loadObjectOBJ("CUBE", "../res/models/cube.obj");
	
	// Current time
	float ct = 0;

	float IDENTITY[16] = { 1, 0, 0, 0, // right
						  0, 1, 0, 0, // up
						  0, 0, 1, 0, // forward
						  0, 0, 0, 1 }; // translate

	glm::mat4 projection, view, model, model1, model2; // Matrices

	//projection = glm::ortho<float>(-20, 20, -20, 20, -1000, 1000);
	//projection = glm::perspective(45.f, 1.f, .1f, 10.f);
	camera.lookAt(glm::vec3(0, 0, 0));
	model = glm::scale(glm::vec3(1, 1, 1)) * glm::translate(glm::vec3(0, 0, 0));
	model1 = glm::scale(glm::vec3(.5f, .5f, .5f)) * glm::translate(glm::vec3(5, 5, 5));
	model2 = glm::scale(glm::vec3(.75f, .75f, .75f)) * glm::translate(glm::vec3(7.5f, 7.5f, 7.5f));

	// Game Loop
	while (window.update())
	{
		time.update();
		input.update();
		view = camera.getView();
		projection = camera.getProjection();
		camera.update(input, time);
		ct += time.getDeltaTime();

		//model = glm::rotate(ct, glm::vec3(0, 1, 0));
		//view = glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // camera position, position to look at, camera direction

		if (input.getKeyState('D') == Input::DOWN)
		{
			ct += time.getDeltaTime();
		}

		if (input.getKeyState('A') == Input::DOWN)
		{
			ct -= time.getDeltaTime();
		}
		// Drawing objects
		draw(gallery.getShader("CAMERA"), gallery.getObject("SAMUS"), glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model));
		draw(gallery.getShader("CAMERA"), gallery.getObject("SPHERE"), glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model1));
		draw(gallery.getShader("CAMERA"), gallery.getObject("CUBE"), glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model2));
	}
	// Terminators
	input.term();
	time.term();
	gallery.term();
	window.term();
	
	return 0;
}