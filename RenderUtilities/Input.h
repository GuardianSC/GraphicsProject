#pragma once

class Input
{
public:
	enum KEY_STATE{ UP, DOWN, PRESS, RELEASE };

	bool Init(const class Window &window);
	bool Update();
	bool Term();

	KEY_STATE getKeyState(int key) const
	{
		return keys[key];
	}

	float getMouseH() const
	{
		return mouseH;
	}

	float getMouseV() const
	{
		return mouseV;
	}

private:
	struct GLFWwindow *winHandle;
	KEY_STATE keys[350];

	double mouseX, mouseY;
	float mouseH, mouseV;
};