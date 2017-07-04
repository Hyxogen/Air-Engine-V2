#include "Window.h"

namespace engine {
	namespace graphics {

		Window::Window(const char* name, const unsigned int width, const unsigned int height) {
			mWidth = width;
			mHeight = height;
			if (glfwInit() == NULL) {
				std::cout << "An error ocurred whilst initializing GLFW" << std::endl;
				return;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_SAMPLES, 4);
			
			//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

			this->mWindow = glfwCreateWindow((int)width, (int)height, name, NULL, NULL);
			if (mWindow == NULL) {
				std::cout << "Could not create window" << std::endl;
				return;
			}
			glfwSetWindowUserPointer(mWindow, this);

			glfwSwapInterval(0);
			
			glfwMakeContextCurrent(mWindow);
			glViewport(0, 0, width, height);

			mInputHandler = new io::InputHandler(mWindow);
		}

		Window::~Window() {
			delete mInputHandler;
			glfwDestroyWindow(mWindow);
			glfwTerminate();
		}

		void Window::setTitle(std::string name) {
			glfwSetWindowTitle(mWindow, name.c_str());
		}

		void Window::Update() const {
			glfwSwapBuffers(mWindow);
			glfwPollEvents();
		}

		bool Window::shouldClose() const {
			return glfwWindowShouldClose(mWindow);
		}

	}
}