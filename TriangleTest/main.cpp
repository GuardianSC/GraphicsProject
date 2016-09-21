#include "crenderutils.h"
#include "GLM\ext.hpp"

void main()
{
	Window context;
	context.init(1350, 750);

	frameBuffer screen = { 0, 1350, 750 };
	frameBuffer frame = makeFrameBuffer(1350, 750, 2);

	Shader simple = loadShader("../res/Shaders/simpleVert.glsl", "../res/Shaders/simpleFrag.glsl");
	Shader post = loadShader("../res/Shaders/postVert.glsl", "../res/Shaders/postFrag.glsl");

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
		clearFramebuffer(frame);

		model = glm::rotate(time, glm::vec3(0, 1, 0)) * glm::translate(glm::vec3(0, -1, 0));

		tdraw(simple, soulspear, screen, model, view, projection, soulspearNormal, soulspearDiffuse, soulspearSpecular);

		tdraw(post, quad, screen, frame.colors[0], frame.colors[1]);
	}

	context.term();
}