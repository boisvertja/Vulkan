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
public:
	Vulkan();
	~Vulkan();
	void initVulkan();
	void cleanup();

private:
	void createInstance();
	bool checkValidationLayerSupport();

	VkInstance instance;

	// Validation layers
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	#ifdef DEBUG
		const bool enableValidationLayers = true;
	#else
		const bool enableValidationLayers = false;
	#endif
};
