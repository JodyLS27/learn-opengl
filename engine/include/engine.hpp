#pragma once

#include "window/window.hpp"

namespace engine
{
	class Engine
	{
	public:
		/**
		* Used to initialize the engine
		**/
		void init();

		/**
		* Start the engine and its main loop
		**/
		int start();

	private:
		engine::Window m_engine_window;

		GLFWwindow* m_window;
	};
}