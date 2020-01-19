#pragma once
#include "Vulkan.h"

class Window
{
public:
	Window();
	~Window();

	inline int getWindowWidth() const;
	inline int getWindowHeight() const;

private:
	void setup();
	void open();
	void cleanup();

	GLFWwindow* window;
	static int WIDTH;
	static int HEIGHT;
};
