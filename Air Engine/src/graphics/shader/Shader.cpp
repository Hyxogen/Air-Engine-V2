#include "Shader.h"

namespace engine {
	namespace graphics {

		Shader::Shader(const uint8* vertexShader, const uint8* fragmentShader, const uint8* geometrySource) {
			mProgramID = glCreateProgram();

			mVertexShaderID = compileShader(vertexShader, GL_VERTEX_SHADER);
			mFragmentShaderID = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
			if (geometrySource != nullptr)
				mGeometryShaderID = compileShader(geometrySource, GL_GEOMETRY_SHADER);

			glAttachShader(mProgramID, mVertexShaderID);
			glAttachShader(mProgramID, mFragmentShaderID);
			if (geometrySource != nullptr)
				glAttachShader(mProgramID, mGeometryShaderID);

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
			if (geometrySource != nullptr)
				glDeleteShader(mGeometryShaderID);
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

		void Shader::setfl32(const char* name, fl32 value) {
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setInt(const char* name, GLint value) {
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUInt(const char* name, uint32 value) {
			glUniform1ui(getUniformLocation(name), value);
		}

		void Shader::setVec3(const char* name, const math::Vector3f& vector) {
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setMat4(const char* name, const math::Matrix4f& matrix) {
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_TRUE, matrix.mElements);
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
				uint32 type = 0;

				glGetActiveUniform(mProgramID, i, maxNameLength, &nameLength, &size, &type, (GLchar*)stringbuffer.data());
				std::string name = std::string(&stringbuffer[0]);

				int location = glGetUniformLocation(mProgramID, name.c_str());
				mCached[name] = location;
			}
		}

		const uint32 Shader::compileShader(const uint8* source, uint32 type) {
			uint32 shaderID = glCreateShader(type);;

			glShaderSource(shaderID, 1, (const GLchar* const*)&source, NULL);
			glCompileShader(shaderID);

			GLint status;

			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
			if (status == GL_FALSE) {
				GLint length;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

				char* buffer = new char[length];

				glGetShaderInfoLog(shaderID, length, 0, buffer);
				
				std::string typeName;
				if (type == GL_VERTEX_SHADER)
					typeName = "vertex shader";
				else if (type == GL_FRAGMENT_SHADER)
					typeName = "fragment shader";
				else if (type == GL_GEOMETRY_SHADER)
					typeName = "geometry shader";
				else
					typeName = "SHADER TYPE NOT FOUND";

				std::cout << "An error ocurred whilst compiling " << typeName.c_str() << std::endl;
				std::cout << buffer << std::endl;
				delete[] buffer;
				return 0;
			}

			return shaderID;
		}


	}
}