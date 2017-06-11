#pragma once
#include <iostream>
#include <GLFW\glfw3.h>

namespace engine {
	namespace graphics {

		class Window {

			GLFWwindow* window;

		public:
			Window(const char* name, const GLsizei width, const GLsizei height);

			~Window();

			void Update() const;

			bool shouldClose() const;
		};

	}
}