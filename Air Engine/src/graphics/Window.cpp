#include "Window.h"

namespace engine {
	namespace graphics {

		Window::Window(const char* name, const GLsizei width, const GLsizei height) {
			if (glfwInit() == NULL) {
				std::cout << "An error ocurred whilst initializing GLFW" << std::endl;
				return;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_RESIZABLE, 0);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			this->window = glfwCreateWindow((int)width, (int)height, name, NULL, NULL);
			if (window == NULL) {
				std::cout << "Could not create window" << std::endl;
				return;
			}

			glfwSwapInterval(1);
			glfwMakeContextCurrent(window);
			glViewport(0, 0, width, height);
		}

		Window::~Window() {
			glfwDestroyWindow(window);
			glfwTerminate();
		}

		void Window::Update() const {
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		bool Window::shouldClose() const {
			return glfwWindowShouldClose(window);
		}

	}
}