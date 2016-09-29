#include "crenderutils.h"
#include "GLM\ext.hpp"

void main()
{
	Window context;
	context.init(1350, 750);

	frameBuffer screen = { 0, 1350, 750 };
	bool isFtex[] = { false, true, false, true };
	frameBuffer gFrame = makeFrameBuffer(1350, 750, 4, isFtex);
	frameBuffer lFrame = makeFrameBuffer(1350, 750, 2);
	frameBuffer nFrame = makeFrameBuffer(1350, 750, 1); /// Blur framebuffer
	frameBuffer sFrame = makeFrameBuffer(1024, 1024, 0); /// temporary, cleared and reused by each light. Resolution can greatly affect quality

	Shader simple = loadShader("../res/Shaders/simpleVert.glsl", "../res/Shaders/simpleFrag.glsl");
	Shader post = loadShader("../res/Shaders/quadVert.glsl", "../res/Shaders/quadFrag.glsl", false);
	Shader blur = loadShader("../res/Shaders/postVert.glsl", "../res/Shaders/postFrag.glsl", false);
	/// Geometry pass
	Shader gPass = loadShader("../res/Shaders/gPassVert.glsl", "../res/Shaders/gPassFrag.glsl");
	/// Lighting pass
	Shader lPass = loadShader("../res/Shaders/lsPassVert.glsl", "../res/Shaders/lsPassFrag.glsl", false, true);
	/// Shadow pass
	Shader sPass = loadShader("../res/Shaders/sPassVert.glsl", "../res/Shaders/sPassFrag.glsl", true, false, false);

	//Texture tex = loadTexture("../res/Textures/30fps.png");

	Geometry quad = makeGeometry(quadVerts, 4, quadTris, 6);
	Geometry soulspear = loadOBJ("../res/Models/soulspear.obj");
	Geometry cube = loadOBJ("../res/Models/cube.obj");
	Geometry sphere = loadOBJ("../res/Models/sphere.obj");

	/// Soulspear textures
	Texture soulspearNormal = loadTexture("../res/Textures/soulspear_normal.tga");
	Texture soulspearDiffuse = loadTexture("../res/Textures/soulspear_diffuse.tga");
	Texture soulspearSpecular = loadTexture("../res/Textures/soulspear_specular.tga");

	const unsigned char normPixels[4] = { 127, 127, 255, 255 };
	Texture vertexNormals = makeTexture(1, 1, 4, normPixels);

	const unsigned char whitePixels[4] = { 255, 255, 255, 255 };
	Texture white = makeTexture(1, 1, 4, whitePixels);

	/// Model matrices
	glm::mat4 spearModel/* = glm::translate(glm::vec3(0, 0, 0))*/;
	glm::mat4 sphereModel = glm::translate(glm::vec3(0.3f, -1, -0.2f));
	glm::mat4 quadModel = glm::rotate(45.f, glm::vec3(0, -1, 0)) * glm::translate(glm::vec3(0, 0, -2)) * glm::scale(glm::vec3(2, 2, 1));

	/// Camera matrices
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(45.f, 1280.f / 720, 1.f, 100.f);

	/// Light matrices/data
	glm::mat4 lightProjection = glm::ortho<float>(-10, 10, -10, 10, -10, 10);

	glm::mat4 redView = glm::lookAt(glm::normalize(-glm::vec3(1, -1, -1)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4 redColor = glm::vec4(1, 0, 0, 1);

	glm::mat4 greenView = glm::lookAt(glm::normalize(-glm::vec3(1, 1, -1)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4 greenColor = glm::vec4(0, 1, 0, 1);

	float time = 0;

	while (context.update())
	{
		time += 0.016f;
		spearModel = glm::rotate(time, glm::vec3(0, 1, 0)) * glm::translate(glm::vec3(0, -2, 0));

		////////////// GEOMETRY PASS \\\\\\\\\\\\\\\/
		clearFramebuffer(gFrame);
		tdraw(gPass, soulspear, gFrame, spearModel, view, projection, soulspearDiffuse, soulspearNormal, soulspearSpecular);
		tdraw(gPass, sphere, gFrame, sphereModel, view, projection, white, vertexNormals, white);
		tdraw(gPass, quad, gFrame, quadModel, view, projection, white, vertexNormals, white);

		////////////// LIGHTING PASS \\\\\\\\\\\\\\/

		clearFramebuffer(lFrame);

		/*tdraw(lPass, quad, lFrame, view, projection, gFrame.colors[0], gFrame.colors[1], gFrame.colors[2], gFrame.colors[2], gFrame.depth);

		tdraw(post, quad, screen, lFrame.colors[0]);

		tdraw(blur, quad, nFrame, gFrame.colors[1]);*/

		/////// Red Light \\\\\\\
		/// Shadow Pre-Pass
		clearFrameBuffer(sFrame);
		tdraw(sPass, soulspear, sFrame, spearModel,  redView, lightProjection);
		tdraw(sPass, sphere,	sFrame, sphereModel, redView, lightProjection);
		tdraw(sPass, quad,		sFrame, quadModel,	 redView, lightProjection);
		// Light Aggregation
		tdraw(lPass, quad, lFrame, view,
			gFrame.colors[0], gFrame.colors[1], gFrame.colors[2], gFrame.colors[3],
			sFrame.depth, redColor, redView, lightProjection);

		/////// Green Light \\\\\\\
		/// Shadow Pre-Pass

		// UNDELETE THIS
		//clearFrameBuffer(sFrame);
		//tdraw(sPass, soulspear, sFrame, spearModel, greenView, lightProjection);
		//tdraw(sPass, sphere, sFrame, sphereModel, greenView, lightProjection);
		//tdraw(sPass, quad, sFrame, quadModel, greenView, lightProjection);
		//// add the green light now.
		//tdraw(lPass, quad, lFrame, view,
		//	gFrame.colors[0], gFrame.colors[1], gFrame.colors[2], gFrame.colors[3],
		//	sFrame.depth, greenColor, greenView, lightProjection);

		clearFrameBuffer(nFrame);

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

*/

		tdraw(post, quad, screen, glm::mat4(), lFrame.colors[0]);
	}
	context.term();
}