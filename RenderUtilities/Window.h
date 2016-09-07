#pragma once

class Window
{
private:
	friend class Input;
	int width;
	int height;
	char title[64];
	bool isInitialized = false;

	// Forward declaration
	struct GLFWwindow *winHandle;

public:
	bool init(int a_width = 1350, int a_height = 800, char *a_title = "Grand Theft Walrus: The ThirtyFirth"); // initialize
	bool update(); // update
	bool term(); // terminate
};