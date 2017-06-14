#pragma once
#include <glad\glad.h>
#include <iostream>
#include <unordered_map>

namespace engine {
	namespace graphics {

		class Shader {

			GLuint mProgramID, mVertexShaderID, mFragmentShaderID;
			std::unordered_map<const char*, GLuint> mCached;

		public:
			Shader(const char* vertexShader, const char* fragmentShader);
			
			void bind();
			
			void unBind();

			void setFloat(const char* name, GLfloat value);

			void setInt(const char* name, GLint value);

			void setUInt(const char* name, GLuint value);

		private:
			const GLuint& getUniformLocation(const char* name);

			const GLuint& compileShader(const char* source, GLenum type);
		};

} }