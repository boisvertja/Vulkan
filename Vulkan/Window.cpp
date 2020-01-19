#include "Window.h"

int Window::WIDTH = 650;
int Window::HEIGHT = 400;

Window::Window() {
    setup();
    open();
}

Window::~Window() {
	cleanup();
}

void Window::setup() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported" << std::endl;

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;
}

void Window::open() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void Window::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

inline int Window::getWindowWidth() const {
    return WIDTH;
}

inline int Window::getWindowHeight() const {
    return HEIGHT;
}
