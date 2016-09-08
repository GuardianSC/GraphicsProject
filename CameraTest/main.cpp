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
#include "procGen.h"

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

	Geometry plane = genGrid(512, 2);
	Texture noise = genNoise(64, 8);

	/// Loading shader(s)
	gallery.loadShader("TEXTURE", "../res/Shaders/texVert.txt", "../res/Shaders/texFrag.txt");
	//gallery.loadShader("CAMERA", "../res/Shaders/cameraVert.txt", "../res/Shaders/cameraFrag.txt");

	/// Loading object(s)
	//gallery.loadObjectOBJ("SAMUS", "../res/Models/samus.obj");
	gallery.loadObjectOBJ("SPHERE", "../res/Models/sphere.obj");
	//gallery.loadObjectOBJ("CUBE", "../res/Models/cube.obj");

	tex = loadTexture("../res/Textures/xray.jpg");
	
	// Current time
	float ct = 0;
	
	// Identity matrix
	float IDENTITY[16] = { 1, 0, 0, 0, // right
						   0, 1, 0, 0, // up
						   0, 0, 1, 0, // forward
						   0, 0, 0, 1 }; // translate

	glm::mat4 projection, view, model , model1/*, model2*/; // Matrices

	//projection = glm::ortho<float>(-20, 20, -20, 20, -1000, 1000);
	projection = glm::perspective(45.f, 1.f, .1f, 50.f);
	//view = glm::lookAt(glm::vec3(10.f, 0.f, 0.f), glm::vec3(0, 0, 0.0f), glm::vec3(0, 1, 0.f));
	model = glm::translate(glm::vec3(0, 0, 0));//  * glm::rotate(180.f, glm::vec3(0, -1, 0));
	model1 = glm::translate(glm::vec3(0, 2, 0));//  * glm::rotate(180.f, glm::vec3(0, -1, 0));
	//model2 = glm::translate(glm::vec3(0, -2, 0));

	camera.jumpTo(glm::vec3(0, 0, 10));
	camera.lookAt(glm::vec3(0, 0, 0));

	// Game Loop
	while (window.update())
	{
		// update systems
		time.update();
		input.update();
		ct += time.getDeltaTime();
		
		view = camera.getView();
		projection = camera.getProjection();
		camera.update(input, time);

		model = glm::translate(glm::vec3(0, 0, 0)) * glm::rotate(ct  * .5f, glm::vec3(0, .5f, 0)) * glm::scale(glm::vec3(.08f, .08f, .08f));
		model1 = glm::translate(glm::vec3(0, 2, 0)) * glm::rotate(ct  * .5f, glm::vec3(0, .5f, 0)) * glm::scale(glm::vec3(.08f, .08f, .08f));
		//model2 = glm::translate(glm::vec3(0, -2, 0)) * glm::rotate(180.f, glm::vec3(0, -1, 0)) * glm::scale(glm::vec3(.08f, .08f, .08f));

		//draw(gallery.getShader("TEXTURE"), gallery.getObject("SAMUS"), tex, glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model), ct);
		draw(gallery.getShader("TEXTURE"), plane, tex, glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model), ct);
		draw(gallery.getShader("TEXTURE"), gallery.getObject("CUBE"), tex, glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model1), ct);
		//draw(gallery.getShader("TEXTURE"), gallery.getObject("SPHERE"), tex, glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model2), ct);
	}
	/// Terminators
	input.term();
	time.term();
	gallery.term();
	window.term();

	return 0;
}