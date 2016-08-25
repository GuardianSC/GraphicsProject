#pragma once



class Window
{
private:
	int width, height;
	char title[64];
	bool isInitialized = false;

	// Forward declaration
	class GLFWwindow *winHandle /* = nullptr*/;

public:
	bool init(int a_width, int a_height, char *a_title); // initialize
	bool step(); // update
	bool term(); // terminate
};