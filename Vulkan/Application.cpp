#include "Vulkan.h"
#include "Application.h"

Application::Application()
{
}

Application::~Application()
{
	cleanup();
}

int Application::run()
{
	try 
	{
		initVulkan();
		loop();
	}
	catch (const std::exception & e) 
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void Application::initVulkan() 
{
	createInstance();
}

void Application::createInstance()
{
	VkApplicationInfo appInfo = {};

	// Vulkan struct type
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	// Tell the Vulkan driver which global extensions and validation layers to use
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

	// Vulkan is platform-agnostic so need extension to interface with window system
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	// Global validation layers to enable
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
	createInfo.enabledLayerCount = 0;

	/* Create Vulkan instance
	 * Vulkan creation functions are typically structured as...
	 * Pointer to struct with creation info
	 * Pointer to custom allocator callbacks
	 * Pointer to the variable that stores the handle to the new object
	*/
	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create Vulkan instance!");
	}

	log("Vulkan instance created successfully!");

	// Store properties of Vulkan extensions
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	// Allocate array to hold extension properties
	std::vector<VkExtensionProperties> extensions(extensionCount);
	
	// Query extension properties
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	log("\nAvailable Extensions:");
	for (const auto& extension : extensions) {
		log(extension.extensionName);
	}
}

void Application::loop()
{
	while (!glfwWindowShouldClose(window.getWindow()))
	{
		glfwPollEvents();
	}
}

void Application::cleanup()
{
	vkDestroyInstance(instance, nullptr);
	window.cleanup();
}
