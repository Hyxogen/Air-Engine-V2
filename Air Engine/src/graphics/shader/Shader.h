#pragma once
#include <glad\glad.h>

namespace engine {
	namespace graphics {

		class Shader {

			GLuint mProgramID, mVertexShaderID, mFragmentShaderID;

			Shader(const char* vertexShader, const char* fragmentShader);

			GLuint compileShader(const char* source, GLenum type);
		};

} }