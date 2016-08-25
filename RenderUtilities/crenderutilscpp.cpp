#define GLEW_STATIC // stops glew from trying to link to dll (which will not be used in this project)
#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#include "crenderutils.h"

void test()
{
	glfwInit();
	glfwTerminate();
}