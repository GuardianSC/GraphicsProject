#include "crenderutils.h"
#include "GLM\ext.hpp"

int main()
{
	Window context;
	context.init(1350, 750);

	frameBuffer screen = { 0, 1350, 750 };

	//Geometry quad = makeGeometry(quadVerts, 4, quadTris, 6);
	Geometry soulspear = loadOBJ("../res/Models/soulspear.obj");

	Texture soulspearNormal = loadTexture("../res/Textures/soulspear_normal.tga");
	Texture soulspearDiffuse = loadTexture("../res/Textures/soulspear_diffuse.tga");
	Texture soulspearSpecular = loadTexture("../res/Textures/soulspear_specular.tga");

	glm::mat4 model, view, projection;

	model = glm::translate(glm::vec3(0, -2, 0)) * glm::scale(glm::vec3(.5f, .5f, .5f));
	view = glm::lookAt(glm::vec3(0, 0, 4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	projection = glm::perspective(45.f, 1280.f / 720, 1.f, 100.f);


	Shader simple = loadShader("../res/Shaders/simpleVert.glsl", "../res/Shaders/simpleFrag.glsl");

	//Texture tex = loadTexture("../res/Textures/30fps.png");

	while (context.update())
	{
		tdraw(simple, soulspear, screen, model, view, projection, soulspearNormal, soulspearDiffuse, soulspearSpecular);
	}

	return 0;
}