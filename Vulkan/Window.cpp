#include "Window.h"

Window::Window()
{
    setup();
}

Window::~Window()
{
}

void Window::setup()
{
    glfwInit();

    // Tell GLFW not to create an OpenGL context by default
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void Window::cleanup()
{
    glfwDestroyWindow(window);
    log("\nWindow Destroyed.");

    glfwTerminate();
    log("GLFW Terminated.");
}

inline int Window::getWindowWidth() const
{
    return WIDTH;
}

inline int Window::getWindowHeight() const
{
    return HEIGHT;
}

GLFWwindow* Window::getWindow()
{
    return window;
}
