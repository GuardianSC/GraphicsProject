#pragma once

class Window
{
private:
	friend class Input;
	int width = 1650;
	int height = 400;
	char title[64] = "Grand Theft Walrus: The Second"; // Default title
	bool isInitialized = false;

	// Forward declaration
	struct GLFWwindow *winHandle;

public:
	bool init(int a_width = 1350, int a_height = 800, char *a_title = "Grand Theft Walrus: The Second"); // initialize
	bool update(); // update
	bool term(); // terminate
};