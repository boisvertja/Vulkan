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
	pickPhysicalDevice();
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
	appInfo.pApplicationName = "Vulkan";
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

// Select graphics card that provides requirements of Vulkan instance
void Vulkan::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	// If no graphics cards support Vulkan
	if (deviceCount == 0)
	{
		throw std::runtime_error("Failed to find GPUs with Vulkan support.");
	}

	// Allocate vector to hold VkPhysicalDevice handles
	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	// Check if any of the physical devices are suitable for the desired Vulkan operations
	// Check if any physical devices meet desired requirements
	for (const auto& device : devices)
	{
		log("Device: " << getDeviceProperties(device).deviceName);

		if (isDeviceSuitable(device))
		{
			physicalDevice = device;
			break;
		}
	}
	
	if (physicalDevice == VK_NULL_HANDLE)
	{
		throw std::runtime_error("Failed to find suitable GPU.");
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

VkPhysicalDeviceProperties Vulkan::getDeviceProperties(VkPhysicalDevice device)
{
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	return deviceProperties;
}

// Find queue families supported by physical device
Vulkan::QueueFamilyIndices Vulkan::findQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndices indices;
	
	// Get list of queue families associated with each device
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	// Need to find at least one queue family that supports 'VK_QUEUE_GRAPHICS_BIT'
	int i = 0;
	for (const auto& queueFamily : queueFamilies)
	{
		if (indices.isComplete())
		{
			break;
		}

		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			indices.graphicsFamily = i;
		}
		i++;
	}

	return indices;
}

bool Vulkan::isDeviceSuitable(VkPhysicalDevice device)
{
	// Determine device name, type, and supported Vulkan version
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);

	// Query texture compression, 64-bit floats
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	// Ensure a device was found that allows the necessary queue family
	QueueFamilyIndices indices = findQueueFamilies(device);

	// Check if device is dedicated graphics card and supports geometry shaders
	return 
		deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
		deviceFeatures.geometryShader && 
		indices.isComplete();
}

void Vulkan::cleanup()
{
	vkDestroyInstance(instance, nullptr);
	log("\nVulkan instance destroyed.");
}
