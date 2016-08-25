#pragma once



class Window
{
private:
	int width = 1650;
	int height = 400;
	char title[64] = "Window";
	bool isInitialized = false;

	// Forward declaration
	struct GLFWwindow *winHandle /* = nullptr*/;

public:
	bool init(int a_width = 1350, int a_height = 800, char *a_title = "Window"); // initialize
	bool step(); // update
	bool term(); // terminate
};