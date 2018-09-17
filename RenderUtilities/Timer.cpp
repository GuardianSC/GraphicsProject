#include "GLFW\glfw3.h"
#include "timer.h"

bool Time::Init()
{
	glfwSetTime(0);
	deltaTime = currentTime = previousTime = 0;
	return true;
}

bool Time::Update()
{
	previousTime = currentTime;
	currentTime = getrealTime();
	deltaTime = currentTime - previousTime;
	return false;
}

bool Time::Term()
{
	return true;
}

float Time::getDeltaTime() const
{
	return deltaTime;
}

float Time::getTotalTime() const
{
	return currentTime;
}

float Time::getrealTime() const
{
	return glfwGetTime();
}
