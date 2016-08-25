#include "Window.h"

// Welcome to the development (context-feature) branch!

int main()
{
	Window window;

	window.init();
	
	while (window.step());

	window.term();

	return 0;
}