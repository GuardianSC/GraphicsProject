#include "GLFW\glfw3.h"
#include "Window.h"
#include "Input.h"
#include <cstring>

bool Input::init(const class Window &window)
{
	memset(keys, 0, 350 * sizeof(KEY_STATE));
	winHandle = window.winHandle;

	// Sets cursor to be invisible in window
	//glfwSetInputMode(winHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return true;
}

bool Input::update()
{
	for (int i = 0; i < 250; ++i)
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
	

	return true;
}

bool Input::term()
{
	return false;
}