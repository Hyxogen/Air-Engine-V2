#include "InputHandler.h"

namespace engine {
	namespace io {

		void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
		void onButtonEvent(GLFWwindow* windowptr, int key, int action, int mods);

		InputHandler::InputHandler(GLFWwindow* window) {
			mWindow = window;

			glfwSetKeyCallback(mWindow, onKeyEvent);
			glfwSetMouseButtonCallback(mWindow, onButtonEvent);
		}

		void InputHandler::update() {
			memset(mPolledKeys, 0, MAX_KEYS);
			memset(mPolledButtons, 0, MAX_BUTTONS);
		}

		void onKeyEvent(GLFWwindow* windowptr, int key, int scancode, int action, int mods) {
			if (key > MAX_KEYS) return;
			using namespace graphics;

			Window* window = (Window*)glfwGetWindowUserPointer(windowptr);
			InputHandler* inputHandler = window->getInputHandler();

			switch (action) {
			case GLFW_PRESS:
				if (inputHandler->keyDown(key)) return;
				inputHandler->mKeys[key] = true;
				inputHandler->mPolledKeys[key] = 1;
				break;
			case GLFW_RELEASE:
				if (!inputHandler->keyDown(key)) return;
				inputHandler->mKeys[key] = false;
				inputHandler->mPolledKeys[key] = 0;
				break;
			default:
				break;
			}
		}

		void onButtonEvent(GLFWwindow* windowptr, int button, int action, int mods) {
			if (button > MAX_BUTTONS) return;
			using namespace graphics;

			Window* window = (Window*)glfwGetWindowUserPointer(windowptr);
			InputHandler* inputHandler = window->getInputHandler();

			switch (action) {
			case GLFW_PRESS:
				if (inputHandler->buttonDown(button)) return;
				inputHandler->mButtons[button] = true;
				inputHandler->mPolledButtons[button] = 1;
				break;
			case GLFW_RELEASE:
				if (!inputHandler->buttonDown(button)) return;
				inputHandler->mButtons[button] = false;
				inputHandler->mButtons[button] = 0;
				break;
			default:
				break;
			}
		}
} }