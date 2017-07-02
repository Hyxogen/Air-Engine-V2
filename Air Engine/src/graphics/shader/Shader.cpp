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

			loadUniforms();

			glDeleteShader(mVertexShaderID);
			glDeleteShader(mFragmentShaderID);
		}

		Shader::~Shader() {
			//for (auto i = mCached.begin(); i != mCached.end(); i++)
			//	delete i->first;
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

#ifdef LEGACY_UNIFORM
		GLint Shader::getUniformLocation(std::string name) {
			if (mCached.find(name) == mCached.end()) {
				GLint location = glGetUniformLocation(mProgramID, name.c_str());
				mCached.emplace(name, location);
				return location;
			}
			return mCached[name];
		}
#endif

		GLint Shader::getUniformLocation(std::string name) {
			if (mCached.find(name) == mCached.end())
				return -1;
			return mCached[name];
		}

		void Shader::loadUniforms() {
			std::vector<char> stringbuffer;
			int uniformCount, maxNameLength;

			glGetProgramiv(mProgramID, GL_ACTIVE_UNIFORMS, &uniformCount);
			glGetProgramiv(mProgramID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);
			stringbuffer.resize(maxNameLength, 0);

			for (int i = 0; i < uniformCount; i++) {
				int nameLength = 0;
				int size = 0;
				GLenum type = 0;

				glGetActiveUniform(mProgramID, i, maxNameLength, &nameLength, &size, &type, (GLchar*)stringbuffer.data());
				std::string name = std::string(&stringbuffer[0]);

				int location = glGetUniformLocation(mProgramID, name.c_str());
				mCached[name] = location;
			}
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