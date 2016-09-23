#include "crenderutils.h"
#include "GLM\ext.hpp"

void main()
{
	Window context;
	context.init(1350, 750);

	frameBuffer screen = { 0, 1350, 750 };
	frameBuffer gFrame = makeFrameBuffer(1350, 750, 4);
	frameBuffer lFrame = makeFrameBuffer(1350, 750, 2);
	frameBuffer nFrame = makeFrameBuffer(1350, 750, 1); /// Blur framebuffer

	Shader simple = loadShader("../res/Shaders/simpleVert.glsl", "../res/Shaders/simpleFrag.glsl");
	Shader post = loadShader("../res/Shaders/quadVert.glsl", "../res/Shaders/quadFrag.glsl", false);
	Shader blur = loadShader("../res/Shaders/postVert.glsl", "../res/Shaders/postFrag.glsl", false);
	/// Geometry pass
	Shader gPass = loadShader("../res/Shaders/gPassVert.glsl", "../res/Shaders/gPassFrag.glsl");
	/// Lighting pass
	Shader lPass = loadShader("../res/Shaders/lPassVert.glsl", "../res/Shaders/lPassFrag.glsl", false, true);

	//Texture tex = loadTexture("../res/Textures/30fps.png");

	Geometry quad = makeGeometry(quadVerts, 4, quadTris, 6);
	Geometry soulspear = loadOBJ("../res/Models/soulspear.obj");
	Geometry cube = loadOBJ("../res/Models/cube.obj");

	Texture soulspearNormal = loadTexture("../res/Textures/soulspear_normal.tga");
	Texture soulspearDiffuse = loadTexture("../res/Textures/soulspear_diffuse.tga");
	Texture soulspearSpecular = loadTexture("../res/Textures/soulspear_specular.tga");
	const unsigned char normPixels[4] = { 127, 127, 255, 255 };
	Texture vertexNormals = makeTexture(1, 1, 4, normPixels);

	glm::mat4 model, view, projection;

	model = glm::translate(glm::vec3(0, 0, 0));
	view = glm::lookAt(glm::vec3(0, 0, 4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	projection = glm::perspective(45.f, 1280.f / 720, 1.f, 100.f);

	float time = 0;

	while (context.update())
	{
		time += 0.016f;
		clearFramebuffer(gFrame);
		clearFramebuffer(lFrame);
		clearFrameBuffer(nFrame);

		model = glm::rotate(time, glm::vec3(0, 1, 0)) * glm::translate(glm::vec3(0, -2, 0));

		// Geometry pass
		tdraw(gPass, soulspear, gFrame, model, view, projection, soulspearDiffuse, soulspearNormal, soulspearSpecular);

		tdraw(gPass, cube, gFrame, model, view, projection, vertexNormals, vertexNormals, vertexNormals);
		tdraw(gPass, quad, gFrame, glm::rotate(45.f, glm::vec3(0, -1, 0)) *
			glm::translate(glm::vec3(0, 0, -2)) * glm::scale(glm::vec3(2, 2, 1)), view, projection, vertexNormals, vertexNormals, vertexNormals);

		// Lighting pass
		tdraw(lPass, quad, lFrame, view, projection, gFrame.colors[0], gFrame.colors[1], gFrame.colors[2], gFrame.colors[2], gFrame.depth);

		tdraw(post, quad, screen, lFrame.colors[0]);

		tdraw(blur, quad, nFrame, gFrame.colors[1]);

		// Debug Rendering Stuff.
		/*for (int i = 0; i < 4; ++i)
		{
			glm::mat4 mod =
				glm::translate(glm::vec3(-.75f + .5*i, 0.75f, 0)) *
				glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
			tdraw(post, quad, screen, gFrame.colors[i], mod);
		}

		glm::mat4 mod =
			glm::translate(glm::vec3(-.75f, 0.25f, 0)) *
			glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		tdraw(post, quad, screen, gFrame.depth, mod);

		mod =
			glm::translate(glm::vec3(-.25f, 0.25f, 0)) *
			glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		tdraw(post, quad, screen, lFrame.colors[0], mod);

		mod =
			glm::translate(glm::vec3(.25f, 0.25f, 0)) *
			glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		tdraw(post, quad, screen, lFrame.colors[1], mod);

		mod =
			glm::translate(glm::vec3(.75f, 0.25f, 0)) *
			glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		tdraw(post, quad, screen, lFrame.colors[2], mod);*/
	}
	context.term();
}