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

// Welcome to the lighting-feature development branch!

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
	//gallery.loadShader("CAMERA", "../res/Shaders/cameraVert.txt", "../res/Shaders/cameraFrag.txt");
	//gallery.loadShader("TEXTURE", "../res/Shaders/textureVert.txt", "../res/Shaders/textureFrag.txt");+
	gallery.loadShader("LIGHTING", "../res/Shaders/phongVert.txt", "../res/Shaders/phongFrag.txt");
	//gallery.loadShader("POST", "../res/Shaders/postVert.txt", "../res/Shaders/postFrag.txt");

	/// Loading object(s)
	//gallery.loadObjectOBJ("SAMUS"      , "../res/Models/samus.obj");
	//gallery.loadObjectOBJ("SPHERE"   , "../res/Models/sphere.obj");
	//gallery.loadObjectOBJ("CUBE"     , "../res/Models/cube.obj");
	gallery.loadObjectOBJ("SOULSPEAR", "../res/Models/soulspear.obj");

	

	Vertex  verts[4] = {   { {-1,-1,0,1 },  {}, {}, {0 ,0}   },
						   { {1,-1,0,1 },   {}, {}, {1, 0}   },
						   { {1, 1,0,1 },   {}, {}, {1, 1}   },
						   { {-1, 1, 0, 1}, {}, {}, {0, 1}   } };

	unsigned tris[] = { 0,1,2,2,3,0 };

	Geometry quad = makeGeometry(verts, 4, tris, 6);

	/// Loading texture(s)
	//tex = loadTexture("../res/Textures/xray.jpg");

	Texture tarray[] = { loadTexture("../res/Textures/soulspear_diffuse.tga"),
		loadTexture("../res/Textures/soulspear_specular.tga"),
		loadTexture("../res/Textures/soulspear_normal.tga") };

	frameBuffer frame = makeFrameBuffer(1350, 750, 3);
	frameBuffer screen = { 0, 1280, 720, 1 };

	// Current time
	float ct = 0;

	// Identity matrix
	float IDENTITY[16] = { 1, 0, 0, 0, // right
		0, 1, 0, 0, // up
		0, 0, 1, 0, // forward
		0, 0, 0, 1 }; // translate

	glm::mat4 projection, view, model, model1, model2; // Matrices

	//projection = glm::ortho<float>(-20, 20, -20, 20, -1000, 1000);
	projection = glm::perspective(45.f, 1.f, .1f, 50.f);
	view = glm::lookAt(glm::vec3(5.f, 5.f, 5.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f)); // eye, center, up
	model = glm::translate(glm::vec3(0, 0, 0));
	model1 = glm::translate(glm::vec3(0, 2, 0));
	model2 = glm::translate(glm::vec3(1, 2, 1));

	camera.jumpTo(glm::vec3(0, 0, 10));
	camera.lookAt(glm::vec3(0, 2, 0));

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

		model1 = /*glm::translate(glm::vec3(0, 2, 0)) * */glm::rotate(ct  * .5f, glm::vec3(0, .5f, 0));

		///Draw functions
		//draw(gallery.getShader("TEXTURE"), plane, noise, glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model), ct);
		drawFB(gallery.getShader("POST"), gallery.getObject("SOULSPEAR"),screen,
											  glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model1), tarray,3);
		/*drawFB(gallery.getShader("POST"), gallery.getObject("SOULSPEAR"), screen,
											  glm::value_ptr(projection), glm::value_ptr(view), glm::value_ptr(model1), tarray, 3);*/
		drawFB(gallery.getShader("POST"), quad, screen, glm::value_ptr(glm::mat4()), glm::value_ptr(glm::mat4()), glm::value_ptr(glm::mat4()), frame.colors, frame.nColors);
	}

	/// Terminators
	input.term();
	time.term();
	gallery.term();
	window.term();

	return 0;
}