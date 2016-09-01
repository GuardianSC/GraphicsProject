#include "GLFW\glfw3.h"
#include "Timer.h"

bool Time::init()
{
	glfwSetTime(0);
	return true;
}

bool Time::update()
{
	previousTime = currentTime;
	currentTime = getrealTime();
	deltaTime = currentTime - previousTime;
	return false;
}

bool Time::term()
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
