#include "Vulkan.h"
#include "Application.h"

Application::Application()
{
}

Application::~Application()
{
	window.cleanup();
}

bool Application::run()
{
	try 
	{
		vulkan.initVulkan();
		loop();
	}
	catch (const std::exception & e) 
	{
		std::cerr << "ERROR::" << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	vulkan.cleanup();
	return EXIT_SUCCESS;
}

void Application::loop()
{
	while (!glfwWindowShouldClose(window.getWindow()))
	{
		glfwPollEvents();
	}
}
