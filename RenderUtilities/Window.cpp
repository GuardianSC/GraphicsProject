#include "GLFW\glfw3.h"
#include "Window.h"
#include <cstring>


bool Window::init(int a_width, int a_height, char * a_title)
{
	width = a_width;
	height = a_height;
	strcpy_s(title, 64, a_title);

	glfwInit();
	winHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);

	glfwMakeContextCurrent(winHandle);
	isInitialized = true;
	return true;
}

bool Window::step()
{
	if (!isInitialized) 
		return false;

	glfwPollEvents();
	glfwSwapBuffers(winHandle);
	return !glfwWindowShouldClose(winHandle);
}

bool Window::term()
{
	glfwDestroyWindow(winHandle);
	glfwTerminate();
	winHandle = nullptr;
	isInitialized = false;
	return false;
}
