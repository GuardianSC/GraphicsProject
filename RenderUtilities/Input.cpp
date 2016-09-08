#include "GLFW\glfw3.h"
#include "Window.h"
#include "Input.h"
#include <cstring>
#include <cstdio>

bool Input::init(const class Window &window)
{
	memset(keys, 0, sizeof(keys));
	winHandle = window.winHandle;
	
	// Sets cursor to be invisible in window
	//glfwSetInputMode(winHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// INITIALIZE ALL THE THINGS
	mouseX = mouseY = mouseH = mouseV = 0;

	return true;
}

bool Input::update()
{
	for (int i = 0; i < 350; ++i)
	{
		int res = glfwGetKey(winHandle, i);
		//GLFW_PRESS, GLFW_RELEASE
		if ((keys[i] == UP || keys[i] == RELEASE) && res == GLFW_PRESS)
		{
			keys[i] = PRESS;
		}
		else if ((keys[i] == DOWN || keys[i] == PRESS) && res == GLFW_RELEASE)
		{
			keys[i] = RELEASE;
		}
		else if (keys[i] == PRESS)
		{
			keys[i] = DOWN;
		}
		else if (keys[i] = RELEASE)
		{
			keys[i] = UP;
		}
	}

	double prevX = mouseX;
	double prevY = mouseY;
	glfwGetCursorPos(winHandle, &mouseX, &mouseY);

	mouseH = mouseX - prevX;
	mouseV = mouseY - prevY;
	
	//printf("%f %f\n", mouseX, mouseY);
	return true;
}

bool Input::term()
{
	return true;
}