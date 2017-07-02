#pragma once
#include <iostream>
#include <GLFW\glfw3.h>
#include "..\io\InputHandler.h"

namespace engine {

	namespace io {
		class InputHandler;
	}

	namespace graphics {

		class Window {

			GLFWwindow* mWindow;
			io::InputHandler* mInputHandler;

		public:
			Window(const char* name, const GLsizei width, const GLsizei height);

			~Window();

			void Update() const;

			bool shouldClose() const;

			inline io::InputHandler* getInputHandler() { return mInputHandler; }
		};

	}
}