#pragma once
#include "Window.h"

class Application
{
public:
	Application();
	~Application();
	int run();

private:
	void initVulkan();
	void createInstance();
	void cleanup();
	void loop();

	Window window = Window();
	VkInstance instance;
};
