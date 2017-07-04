#pragma once
#include <glad/glad.h>
#include <vector>
#include <algorithm>
#include "BufferObject.h"
#include "Buffer.h"

namespace engine {
	namespace buffer {

		class VertexArray : public Buffer {

			std::vector<float> mData;
			std::vector<unsigned int> mIndices;
			GLuint VBO = 0, EBO = 0;

		public:
			VertexArray(std::vector<float>&& data, std::vector<unsigned int>&& indices, int vertexSize = 3);

			~VertexArray();

			void bind() const;
			
			void unBind() const;

			void assignAttribPointer(GLuint index, unsigned int size, GLenum dataType, bool normalized = false, GLuint stride = 0,
				void* offset = 0, const BufferObject* bufferObject = nullptr);

			void setAttribDivisor(GLuint index, GLuint value) const;

			inline const std::vector<float>& getData() const { return mData; }

			inline const std::vector<unsigned int>& getIndices() const { return mIndices; }
		};

	}
}
