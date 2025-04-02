#include "window/window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

engine::Window::Window() : m_window(nullptr) {}

engine::Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}


void engine::Window::init()
{
	// Initialize the window attributes
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_screen_width, m_screen_height, "Fluid Solver", nullptr, nullptr);

	// Crash if the window is null
	if (!m_window)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);


	// Pass GLAD the function to load the address of the OpenGL function pointer which is OS Specific.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fail to Initialize GLAD\n";
		return;
	}

	// Viewport
	glViewport(0, 0, m_screen_width, m_screen_height);

	// Event callbacks
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

}

GLFWwindow* engine::Window::getGLFWwindow() const
{
	return m_window;
}

// GLFW Events
void engine::Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	std::cout << "\n\n --- Window resized ---\n\n";
}

void engine::Window::process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
