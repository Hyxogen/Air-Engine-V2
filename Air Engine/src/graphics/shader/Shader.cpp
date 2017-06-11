#include "Shader.h"

namespace engine {
	namespace graphics {

		Shader::Shader(const char* vertexShader, const char* fragmentShader) {
			mProgramID = glCreateProgram();

			mVertexShaderID = compileShader(vertexShader, GL_VERTEX_SHADER);
			mFragmentShaderID = compileShader(vertexShader, GL_FRAGMENT_SHADER);

			glAttachShader(mProgramID, mVertexShaderID);
			glAttachShader(mProgramID, mFragmentShaderID);

			glLinkProgram(mProgramID);
			glValidateProgram(mProgramID);
			//TODO add error checking and shader compile method
		}


	}
}