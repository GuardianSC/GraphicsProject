#include "crenderutils.h"
#include "GLM\ext.hpp"
#include <vector>

void main()
{
	Window context;
	FlyCamera camera;
	Input input;
	Time time;
	context.Init(1350, 750);
	time.Init();
	input.Init(context);

	/// Framebuffers
	FrameBuffer screen = { 0, 1350, 750 };
	bool isFtex[] = { false, true, false, true };
	FrameBuffer gFrame = makeFrameBuffer(1350, 750, 4, isFtex); // Geometry framebuffer
	FrameBuffer lFrame = makeFrameBuffer(1350, 750, 2); // Lighting framebuffer
	FrameBuffer bFrame = makeFrameBuffer(1350, 750, 1); // Bloom framebuffer
	FrameBuffer pFrame = makeFrameBuffer(1350, 750, 1); // Post process framebuffer
	FrameBuffer sFrame = makeFrameBuffer(1024, 1024, 0); // Temporary, cleared and reused by each light. Resolution can greatly affect quality

	///Shaders
	// Geometry pass is basically phong so phong shaders aren't really needed. And it works (using phong hangs program at startup)
	// Keeping in case I want to fix, or maybe mess with them for whatever reason
	//Shader phong = loadShader("../res/Shaders/phongVert.glsl", "../res/Shaders/phongFrag.glsl");
	Shader quadS = loadShader("../res/Shaders/quadVert.glsl" , "../res/Shaders/quadFrag.glsl", false);
	Shader post  = loadShader("../res/Shaders/postVert.glsl" , "../res/Shaders/postFrag.glsl");	// Post processing pass
	Shader gPass = loadShader("../res/Shaders/gPassVert.glsl", "../res/Shaders/gPassFrag.glsl"); // Geometry pass	
	Shader lPass = loadShader("../res/Shaders/lsPassVert.glsl", "../res/Shaders/lsPassFrag.glsl", false, true); // Lighting pass	
	Shader sPass = loadShader("../res/Shaders/sPassVert.glsl", "../res/Shaders/sPassFrag.glsl", true, false, false); // Shadow pass	
	Shader bPass = loadShader("../res/Shaders/bPassVert.glsl", "../res/Shaders/bPassFrag.glsl", true, false, false); // Bloom Pass
	Shader waterS = loadShader("../res/Shaders/quadVert.glsl", "../res/Shaders/quadFrag.glsl", false); // Water shader
	
	/// Geometry/Models
	Geometry quad	   = makeGeometry(quadVerts, 4, quadTris, 6); // Wall
	Geometry quadWater = makeGeometry(quadVerts, 4, quadTris, 6); // Water
	Geometry soulspear = loadOBJ("../res/Models/soulspear.obj");
	Geometry cube	   = loadOBJ("../res/Models/cube.obj");
	Geometry sphere    = loadOBJ("../res/Models/sphere.obj");

	/// Textures
	Texture soulspearNormal   = loadTexture("../res/Textures/soulspear_normal.tga");
	Texture soulspearDiffuse  = loadTexture("../res/Textures/soulspear_diffuse.tga");
	Texture soulspearSpecular = loadTexture("../res/Textures/soulspear_specular.tga");

	Texture wallTex   = loadTexture("../res/Textures/Weavesilk9.png");
	Texture sphereTex = loadTexture("../res/Textures/sphere.jpg");
	Texture cubeTex   = loadTexture("../res/Textures/cube.jpg");
	Texture spaceTex  = loadTexture("../res/Textures/space.jpg");
	Texture waterTex  = loadTexture("../res/Textures/water.jpg");

	const unsigned char normPixels[4] = { 127, 127, 255, 255 };
	Texture vertexNormals = makeTexture(1, 1, 4, normPixels);

	const unsigned char whitePixels[4] = { 255, 255, 255, 255 };
	Texture white = makeTexture(1, 1, 4, whitePixels);

	// Model matrices
	glm::mat4 spearModel/*   = glm::translate(glm::vec3(0, 0, 0))*/;
	glm::mat4 sphereModel    = glm::translate(glm::vec3(0.5f, -1.25, -0.25f));
	glm::mat4 cubeModel      = glm::translate(glm::vec3(5, 2, 5));
	glm::mat4 quadModel      = glm::rotate(45.f, glm::vec3(0, -1, 0)) * glm::translate(glm::vec3(0, 0, -5)) * glm::scale(glm::vec3(10, 10, 10));
	glm::mat4 quadWaterModel = glm::rotate(33.f, glm::vec3(-1, 0, 0)) * glm::translate(glm::vec3(-5, 0, -5)) * glm::scale(glm::vec3(5, 5, 5));
	
	// Camera matrices
	glm::mat4 view = glm::lookAt(glm::vec3(-5, 0, -5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(45.f, 1280.f / 720, 1.f, 100.f);

	// Light matrices/data
	glm::mat4 lightProjection = glm::ortho<float>(-10, 10, -10, 10, -10, 10);

	glm::mat4 redView    = glm::lookAt(glm::normalize(-glm::vec3(0, -1, -1)), glm::vec3(0, 0, 0), glm::vec3(2, 1, 0));
	glm::vec4 redColor   = glm::vec4(1, 0, 0, 1);
	glm::mat4 red1View   = glm::lookAt(glm::normalize(-glm::vec3(0, 0, 0)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glm::mat4 greenView  = glm::lookAt(glm::normalize(-glm::vec3(1, -1, -1)), glm::vec3(0, -1, 0), glm::vec3(0, 1, 0));
	glm::vec4 greenColor = glm::vec4(0, 1, 0, 1);
	glm::mat4 green1View = glm::lookAt(glm::normalize(-glm::vec3(0, 0, 0)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glm::mat4 blueView  = glm::lookAt(glm::normalize(-glm::vec3(1, -1, -1)), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	glm::vec4 blueColor = glm::vec4(0, 0, 1, 1);
	glm::mat4 blue1View = glm::lookAt(glm::normalize(-glm::vec3(0, 0, 0)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	// Time (current time)
	float ct = 0;

	camera.jumpTo(glm::vec3(2, 0, 2));
	camera.lookAt(glm::vec3(2, 2, 0));

	// Game loop
	while (context.Update())
	{
		time.Update();
		input.Update();
		ct += 0.016f;

		spearModel  = glm::rotate(ct, glm::vec3(0, 1, 0)) * glm::translate(glm::vec3(0, -2, 0));
		cubeModel   = glm::rotate(ct, glm::vec3(1, -1, 0));
		sphereModel = glm::rotate(ct, glm::vec3(0, 1, 0)) * glm::translate(glm::vec3(0.5f, -1.25, -0.25f));

		view = camera.getView();
		projection = camera.getProjection();
		camera.update(input, time);

#pragma region Geometry
		////////////// GEOMETRY PASS //////////////
		clearFramebuffer(gFrame);
		tdraw(gPass, soulspear, gFrame, spearModel, view, projection, soulspearDiffuse, soulspearNormal, soulspearSpecular);
		tdraw(gPass, sphere, gFrame, sphereModel, view, projection, sphereTex, vertexNormals, white);
		tdraw(gPass, cube, gFrame, cubeModel, view, projection, cubeTex, vertexNormals, white);
		tdraw(gPass, quad, gFrame, quadModel, view, projection, spaceTex, vertexNormals, white);
		tdraw(gPass, quadWater, gFrame, quadWaterModel, view, projection, waterTex, vertexNormals, white);

#pragma region Lighting&Shadow
		////////////// LIGHTING PASS //////////////
		clearFramebuffer(lFrame);
		//tdraw(phong, soulspear, lFrame, spearModel, view, projection, soulspearDiffuse, soulspearNormal, soulspearSpecular);

		////////////// Red Light //////////////
		/// Shadow Pre-Pass
		clearFrameBuffer(sFrame);
		tdraw(sPass, soulspear, sFrame, spearModel,  redView, lightProjection);
		tdraw(sPass, sphere,    sFrame, sphereModel, redView, lightProjection);
		tdraw(sPass, cube,		sFrame, cubeModel,	 redView, lightProjection);
		tdraw(sPass, quad,		sFrame, quadModel,   redView, lightProjection);
		// Light Aggregation
		tdraw(lPass, quad, lFrame, view, gFrame.colors[0], gFrame.colors[1],
			  gFrame.colors[2], gFrame.colors[3], sFrame.depth, redColor, redView, lightProjection);
		tdraw(lPass, quad, lFrame, view, gFrame.colors[0], gFrame.colors[1],
			gFrame.colors[2], gFrame.colors[3], sFrame.depth, redColor, red1View, lightProjection);

		////////////// Green Light //////////////
		/// Shadow Pre-Pass
		clearFrameBuffer(sFrame);
		tdraw(sPass, soulspear, sFrame, spearModel,  greenView, lightProjection);
		tdraw(sPass, sphere,    sFrame, sphereModel, greenView, lightProjection);
		tdraw(sPass, cube,      sFrame, cubeModel,   greenView, lightProjection);
		tdraw(sPass, quad,      sFrame, quadModel,	 greenView, lightProjection);
		// Light Aggregation
		tdraw(lPass, quad, lFrame, view, gFrame.colors[0], 
			  gFrame.colors[1], gFrame.colors[2], gFrame.colors[3], sFrame.depth, greenColor, greenView, lightProjection);
		tdraw(lPass, quad, lFrame, view, gFrame.colors[0],
			gFrame.colors[1], gFrame.colors[2], gFrame.colors[3], sFrame.depth, greenColor, green1View, lightProjection);

		////////////// Blue Light //////////////
		/// Shadow Pre-Pass
		clearFrameBuffer(sFrame);
		tdraw(sPass, soulspear, sFrame, spearModel, blueView, lightProjection);
		tdraw(sPass, sphere, sFrame, sphereModel, blueView, lightProjection);
		tdraw(sPass, cube, sFrame, cubeModel, blueView, lightProjection);
		tdraw(sPass, quad, sFrame, quadModel, blueView, lightProjection);
		// Light Aggregation
		tdraw(lPass, quad, lFrame, view, gFrame.colors[0],
			gFrame.colors[1], gFrame.colors[2], gFrame.colors[3], sFrame.depth, blueColor, blueView, lightProjection);
		tdraw(lPass, quad, lFrame, view, gFrame.colors[0],
			gFrame.colors[1], gFrame.colors[2], gFrame.colors[3], sFrame.depth, blueColor, blue1View, lightProjection);
#pragma endregion

#pragma region Miscellaneous_Effects
		////////////// POST PROCESS //////////////
		clearFrameBuffer(pFrame);
		tdraw(post, quad, pFrame, gFrame.colors[0], lFrame.colors[0]);

		////////////// BLOOM //////////////
		clearFrameBuffer(bFrame);
		tdraw(bPass, quad, bFrame, pFrame.colors[0], ct, lFrame.colors[1]);

		////////////// Water //////////////
		//tdraw(waterS, quadWater, gFrame, quadWaterModel, view, projection, waterTex, vertexNormals, white);
#pragma endregion

		/// Particles
		/*GLuint maxParticles = 500;
		std::vector<Particle> particles; // List of particles (active and deactive)

		for (GLuint i = 0; i < maxParticles; i++)
			particles.push_back(Particle()); // instantiate with default particle struct

		// Each frame, spawn new particles and update older particles' values
		GLuint newParticles = 2;
		// Add particles
		for (GLuint i = 0; i < newParticles; i++)
		{
			int unusedParticle = FirstUnusedParticle();
			RespawnParticle(particles[unusedParticle], object, offset);
		}
		// Update particles
		for (GLuint i = 0; i < maxParticles; ++i)
		{
			Particle &p = particles[i];
			p.life -= ct;
			// Particle is alive so update values
			if (p.life > 0.0f)
			{
				p.position -= p.velocity * ct;
				p.color.a -= ct * 2.5;
			}
		}

		GLuint lastUsedParticle = 0;
		GLuint FirstUnusedParticle()
		{
			// search from last used particle, should return almost instantly
			for (GLuint i = lastUsedParticle; i < maxParticles; ++i)
			{
				if (particles[i].life <= 0.0f)
				{
					lastUsedParticle = i;
					return i;
				}
			}
			// Otherwise do a linear search
			for (GLuint i = 0; i < lastUsedParticle; ++i)
			{
				if (particles[i].life <= 0.0f)
				{
					lastUsedParticle = i;
					return i;
				}
			}

			lastUsedParticle = 0;
			return 0;
		}*/

		

		// Main screen/camera
		tdraw(quadS, quad, screen, glm::mat4(), pFrame.colors[0]);

		/// Debug Rendering Stuff.
		//for (int i = 0; i < 4; ++i)
		//{
		//	glm::mat4 mod =
		//		glm::translate(glm::vec3(-.75f + .5*i, 0.75f, 0)) *
		//		glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		//	tdraw(quadS, quad, screen, mod, gFrame.colors[i]);// , pFrame.colors[0]);
		//}

		//glm::mat4 mod =
		//	glm::translate(glm::vec3(-.75f, 0.25f, 0)) *
		//	glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		//tdraw(quadS, quad, screen, mod, bFrame.colors[0]);

		/*glm::mat4 mod =
			glm::translate(glm::vec3(-.75f, 0.25f, 0)) *
			glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		tdraw(post, quad, screen, mod, gFrame.depth);

		mod =
			glm::translate(glm::vec3(-.25f, 0.25f, 0)) *
			glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		tdraw(post, quad, screen, mod, lFrame.colors[0]);

		mod =
			glm::translate(glm::vec3(.25f, 0.25f, 0)) *
			glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		tdraw(post, quad, screen, mod, lFrame.colors[1]);

		mod =
			glm::translate(glm::vec3(.75f, 0.25f, 0)) *
			glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		tdraw(post, quad, screen, mod, lFrame.colors[2]);*/
		
	}
	input.Term();
	time.Term();
	context.Term();
}