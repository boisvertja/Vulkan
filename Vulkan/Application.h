#pragma once
#include "Vulkan.h"
#include "Window.h"

class Application
{
public:
	Application();
	~Application();
	bool run();

private:
	void loop();

	Vulkan vulkan = Vulkan();
	Window window = Window();
};
