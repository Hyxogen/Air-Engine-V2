#include "Shader.h"

namespace engine {
	namespace graphics {

		Shader::Shader(const char* vertexShader, const char* fragmentShader) {
			mProgramID = glCreateProgram();

			mVertexShaderID = compileShader(vertexShader, GL_VERTEX_SHADER);
			mFragmentShaderID = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

			glAttachShader(mProgramID, mVertexShaderID);
			glAttachShader(mProgramID, mFragmentShaderID);

			glLinkProgram(mProgramID);
			glValidateProgram(mProgramID);

			GLint status;
			glGetProgramiv(mProgramID, GL_LINK_STATUS, &status);
			if (status == GL_FALSE) {
				GLint length;
				glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &length);

				char* buffer = new char[length];
				glGetProgramInfoLog(mProgramID, length, NULL, buffer);

				std::cout << "And error ocurred whilst linking the program(" << mProgramID << ")" << std::endl;
				std::cout << buffer << std::endl;

				delete[] buffer;
				return;
			}

			glDeleteShader(mVertexShaderID);
			glDeleteShader(mFragmentShaderID);
		}

		void Shader::bind() {
			glUseProgram(mProgramID);
		}

		void Shader::unBind() {
			glUseProgram(0);
		}

		void Shader::setFloat(const char* name, GLfloat value) {
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setInt(const char* name, GLint value) {
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUInt(const char* name, GLuint value) {
			glUniform1ui(getUniformLocation(name), value);
		}

		void Shader::setMat4(const char* name, const math::Matrix4f& matrix) {
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.mElements);
		}

		const GLuint Shader::getUniformLocation(const char* name) {
			if (mCached.find(name) == mCached.end()) {
				GLuint location = glGetUniformLocation(mProgramID, name);
				mCached.emplace(name, location);
				return location;
			}
			return mCached[name];
		}

		const GLuint Shader::compileShader(const char* source, GLenum type) {
			GLuint shaderID = glCreateShader(type);;

			glShaderSource(shaderID, 1, &source, NULL);
			glCompileShader(shaderID);

			GLint status;

			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
			if (status == GL_FALSE) {
				GLint length;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

				char* buffer = new char[length];

				glGetShaderInfoLog(shaderID, length, 0, buffer);
				
				std::cout << "An error ocurred whilst compiling " << ((type == GL_VERTEX_SHADER) ? "vertex shader" : "fragment shader") << std::endl;
				std::cout << buffer << std::endl;
				delete[] buffer;
				return 0;
			}

			return shaderID;
		}


	}
}