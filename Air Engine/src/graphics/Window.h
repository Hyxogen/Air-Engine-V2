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
			unsigned int mWidth, mHeight;

		public:
			Window(const char* name, const unsigned int width, const unsigned int height);

			~Window();

			void Update() const;

			bool shouldClose() const;

			inline io::InputHandler* getInputHandler() { return mInputHandler; }

			inline unsigned int getWidth() { return mWidth; }

			inline unsigned int getHeight() { return mHeight; }

			inline float getAspectRatio() { return (float)mWidth / (float) mHeight; }
		};

	}
}