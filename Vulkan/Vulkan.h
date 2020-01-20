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
