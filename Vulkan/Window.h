#pragma once
#include "Vulkan.h"

class Window
{
public:
	Window();
	~Window();

	inline int getWindowWidth() const;
	inline int getWindowHeight() const;
	GLFWwindow* getWindow();

	void setup();
	void cleanup();

private:
	GLFWwindow* window;
	const int WIDTH = 650;
	const int HEIGHT = 400;
};
