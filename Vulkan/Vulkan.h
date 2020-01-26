#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

// Functional
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

// Data Structures
#include <map>
#include <optional>
#include <string>
#include <vector>

// User-Defined
#ifdef DEBUG
	#define log(str) std::cout << str << std::endl
#else
	#define log(str)
#endif

class Vulkan
{
private:
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;

		bool isComplete()
		{
			return graphicsFamily.has_value();
		}
	};

public:
	Vulkan();
	~Vulkan();
	void initVulkan();
	void cleanup();

private:
	// Validation layers
	const std::vector<const char*> validationLayers =
	{
		"VK_LAYER_KHRONOS_validation",
		"VK_LAYER_LUNARG_standard_validation"
	};

	void createInstance();
	void pickPhysicalDevice();
	void createLogicalDevice();
	bool checkValidationLayerSupport();
	bool isDeviceSuitable(VkPhysicalDevice device);
	VkPhysicalDeviceProperties getDeviceProperties(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	VkInstance instance;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice logicalDevice;
	VkQueue graphicsQueue;

	#ifdef DEBUG
		const bool enableValidationLayers = true;
	#else
		const bool enableValidationLayers = false;
	#endif
};
