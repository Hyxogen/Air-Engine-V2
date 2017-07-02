#pragma once
#include <glad\glad.h>
#include <iostream>
#include <unordered_map>
#include "../../math/Math.h"

namespace engine {
	
	namespace graphics {

		class Shader {

			GLuint mProgramID, mVertexShaderID, mFragmentShaderID;
			std::unordered_map<std::string, GLint> mCached;

		public:
			Shader(const char* vertexShader, const char* fragmentShader);
			
			~Shader();

			void bind();
			
			void unBind();

			void setFloat(const char* name, GLfloat value);

			void setInt(const char* name, GLint value);

			void setUInt(const char* name, GLuint value);

			void setMat4(const char* name, const math::Matrix4f& matrix);

			GLint getUniformLocation(std::string name);
		private:
			void loadUniforms();
			
			const GLuint compileShader(const char* source, GLenum type);
		};

} }