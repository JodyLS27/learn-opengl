#pragma once
#include <iostream>

struct GLFWwindow;

namespace engine
{
	class Window
	{
	public:
		Window();
		~Window();

		/**
		* Initialize a GLFW window
		**/
		void init();

		/**
		* Used to return the window object from GLFW
		**/
		GLFWwindow* getGLFWwindow() const;

		// --- GLWF Events ---

		/**
		* called when the window is resized and sets the glViewport to the current window size
		* @NOTE: Made static as GLFW requires callback functions to have a C-style function signature (
		**/
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		/**
		* Used for Input processing like Keyboard, Mouse or controller
		**/
		void process_input(GLFWwindow* window);

	private:
		// Settings
		const int m_screen_width = 800;
		const int m_screen_height = 600;

		GLFWwindow* m_window;

	};
}
