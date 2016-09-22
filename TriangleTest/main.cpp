#include "crenderutils.h"
#include "GLM\ext.hpp"

void main()
{
	Window context;
	context.init(1350, 750);

	frameBuffer screen = { 0, 1350, 750 };
	frameBuffer gframe = makeFrameBuffer(1350, 750, 4);
	frameBuffer lframe = makeFrameBuffer(1350, 750, 2);

	Shader simple = loadShader("../res/Shaders/simpleVert.glsl", "../res/Shaders/simpleFrag.glsl");
	Shader post = loadShader("../res/Shaders/postVert.glsl", "../res/Shaders/postFrag.glsl");
	Shader quad = loadShader("../res/Shaders/quadVert.glsl", "../res/Shaders/quadFrag.glsl");
	// Geometry pass
	Shader gPass = loadShader("../res/Shaders/gPassVert.glsl", "../res/Shaders/gPassFrag.glsl");
	// Lighting pass
	Shader lPass = loadShader("../res/Shaders/lPassVert.glsl", "../res/Shaders/lPassFrag.glsl");

	//Texture tex = loadTexture("../res/Textures/30fps.png");

	Geometry quad = makeGeometry(quadVerts, 4, quadTris, 6);
	Geometry soulspear = loadOBJ("../res/Models/soulspear.obj");

	Texture soulspearNormal = loadTexture("../res/Textures/soulspear_normal.tga");
	Texture soulspearDiffuse = loadTexture("../res/Textures/soulspear_diffuse.tga");
	Texture soulspearSpecular = loadTexture("../res/Textures/soulspear_specular.tga");

	glm::mat4 model, view, projection;

	model = glm::translate(glm::vec3(0, 0, 0));
	view = glm::lookAt(glm::vec3(0, 0, 4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	projection = glm::perspective(45.f, 1280.f / 720, 1.f, 100.f);
	float time = 0;

	while (context.update())
	{
		time += 0.016f;
		clearFramebuffer(gframe);
		clearFramebuffer(lframe);

		model = glm::rotate(time, glm::vec3(0, 1, 0)) * glm::translate(glm::vec3(0, -1, 0));

		tdraw(gPass, soulspear, gframe, model, view, projection, soulspearDiffuse, soulspearNormal, soulspearSpecular);

		//tdraw(lPass, quad, lframe, view, projection, gframe.colors[0], gframe.colors[1], gframe.colors[2], gframe.colors[2], gframe.depth);

		//tdraw(post, quad, screen, lframe.colors[0]);
	}

	context.term();
}