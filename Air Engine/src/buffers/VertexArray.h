#pragma once
#include <glad/glad.h>
#include <vector>
#include <algorithm>
#include "BufferObject.h"
#include "Buffer.h"

namespace engine {
	namespace buffer {

		class VertexArray : public Buffer {

			BufferObject* mElementBuffer, *mVertexBuffer;

		public:
			VertexArray(std::vector<float> data, std::vector<unsigned int> indices);

			VertexArray(const void* data, GLuint size, std::vector<unsigned int> indices);

			~VertexArray();

			void bind() const;
			
			void unBind() const;

			void assignAttribPointer(GLuint index, unsigned int size, GLenum dataType, GLuint stride = 0,
				void* offset = 0, const BufferObject* bufferObject = nullptr, GLboolean normalized = GL_FALSE);

			void setAttribDivisor(GLuint index, GLuint value) const;

			inline unsigned int getVertexCount() const { return mVertexBuffer->getSize() / sizeof(float); }

			inline unsigned int getIndicesCount() const { return mElementBuffer->getSize() / sizeof(unsigned int); }

			inline const BufferObject* const getElementBuffer() const { return mElementBuffer; }

			inline const BufferObject* const getVertexBuffer() const { return mVertexBuffer; }
		};

	}
}
