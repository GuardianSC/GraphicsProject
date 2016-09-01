#include "Window.h"
#include "Vertex.h"
#include "crenderutils.h"
#include "gallery.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

// Welcome to the camera-feature development branch!

int main()
{
	Window window;
	Gallery gallery;

	window.init(1350, 750);
	gallery.init();

	gallery.loadShader("CAMERA", "../res/shaders/cameraVert.txt", "../res/shaders/cameraFrag.txt");

	gallery.loadObjectOBJ("SPHERE", "../res/models/sphere.obj");
	gallery.loadObjectOBJ("CUBE", "../res/models/cube.obj");
	//gallery.loadObjectOBJ("PANDA", "../res/models/Panda 1.obj");

	float time = 0;

	float IDENTITY[16] = {1, 0, 0, 0, // right
						  0, 1, 0, 0, // up
						  0, 0, 1, 0, // forward
						  0, 0, 0, 1}; // translate

	glm::mat4 projection, view, model;

	projection = glm::ortho<float>(-2, 2, -2, 2, -10, 10);
	//projection = glm::perspective(45.f, 1.f, .1f, 10.f);
	model = glm::scale(glm::vec3(1.f, 1.f, 1.f)) * glm::translate(glm::vec3(.5f, .1f, 2.f)), glm::rotate(time, glm::vec3(0, 1, 0));
	view = glm::lookAt(glm::vec3(0.f, 0.f, 0.f), glm::vec3(5.f, 5.f, 5.f), glm::vec3(0.f, 1.f, 0.f));

	while (window.step())
	{
		time += 0.1667f;
		draw(gallery.getShader("CAMERA"), gallery.getObject("SPHERE"), glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model));
		draw(gallery.getShader("CAMERA"), gallery.getObject("CUBE"), glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model));
		//draw(gallery.getShader("CAMERA"), gallery.getObject("PANDA"), glm::value_ptr(model), glm::value_ptr(view), glm::value_ptr(projection));
	}
	gallery.term();
	window.term();
	return 0;
}