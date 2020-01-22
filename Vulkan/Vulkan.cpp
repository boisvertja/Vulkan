#include "Vulkan.h"

Vulkan::Vulkan()
{
}

Vulkan::~Vulkan()
{
}

void Vulkan::initVulkan()
{
	createInstance();
}

void Vulkan::createInstance()
{
	// Ensure all appropriate validation layers are supported
	if (enableValidationLayers && !checkValidationLayerSupport())
	{
		throw std::runtime_error("Some validation layers are not available");
	}

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

	// Include the validation layer names if they are available
	if (enableValidationLayers)
	{
		// Set the application's number of layers equal to the size of the 'validationLayers' vector
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());

		// Set the names equal to the data of 'validationLayers'
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

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

// Checks if all validation layers are supported
bool Vulkan::checkValidationLayerSupport()
{
	// List all the available layers
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	// Store the properties into the layer properties vector
	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	// Check if all the layers in 'validationLayers' exist in 'availableLayers'
	for (const char* layerName : validationLayers)
	{
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
		{
			return false;
		}
	}

	log("All validation layers available.");
	return true;
}

void Vulkan::cleanup()
{
	vkDestroyInstance(instance, nullptr);
	log("\nVulkan instance destroyed.");
}
