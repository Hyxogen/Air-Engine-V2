#pragma once
#include "..\graphics\Window.h"
#define MAX_KEYS 300
#define MAX_BUTTONS 3

namespace engine {
	namespace io {

		class InputHandler {

			GLFWwindow* mWindow;
			bool mKeys[MAX_KEYS], mButtons[MAX_BUTTONS], mPolledKeys[MAX_KEYS], mPolledButtons[MAX_BUTTONS];

		public:
			InputHandler(GLFWwindow* window);

			void update();

			inline bool keyDown(unsigned int key) { return mKeys[key]; }
			
			inline bool keyPressed(unsigned int key) { return mPolledKeys[key] == 1; }

			inline bool buttonDown(unsigned int button) { return mButtons[button]; }

			inline bool buttonPressed(unsigned int button) { return mPolledButtons[button] == 1; }

		private:
			friend void onKeyEvent(GLFWwindow* windowptr, int key, int scancode, int action, int mods);

			friend void onButtonEvent(GLFWwindow* window, int button, int action, int mods);
		};
} }