#pragma once
#include <glad\glad.h>
#include <iostream>
#include <unordered_map>
#include "../../math/Math.h"
#include "..\..\DataTypes.h"

namespace engine {
	
	namespace graphics {

		class Shader {

			uint32 mProgramID, mVertexShaderID, mFragmentShaderID, mGeometryShaderID;
			std::unordered_map<std::string, GLint> mCached;

		public:
			Shader(const uint8* vertexShader, const uint8* fragmentShader, const uint8* geometrySource = nullptr);
			
			~Shader();

			void bind();
			
			void unBind();

			void setfl32(const char* name, fl32 value);

			void setInt(const char* name, GLint value);

			void setUInt(const char* name, uint32 value);

			void setVec3(const char* name, const math::Vector3f& vector);

			void setMat4(const char* name, const math::Matrix4f& matrix);

			GLint getUniformLocation(std::string name);
		private:
			void loadUniforms();
			
			const uint32 compileShader(const uint8* source, uint32 type);
		};

} }