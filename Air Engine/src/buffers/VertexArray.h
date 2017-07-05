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
			VertexArray(std::vector<fl32> data, std::vector<uint32> indices);

			VertexArray(const void* data, uint32 size, std::vector<unsigned int> indices);

			~VertexArray();

			void bind() const;
			
			void unBind() const;

			void assignAttribPointer(uint32 index, unsigned int size, uint32 dataType, uint32 stride = 0,
				void* offset = 0, const BufferObject* bufferObject = nullptr, GLboolean normalized = GL_FALSE);

			void setAttribDivisor(uint32 index, uint32 value) const;

			inline unsigned int getVertexCount() const { return mVertexBuffer->getSize() / sizeof(fl32); }

			inline unsigned int getIndicesCount() const { return mElementBuffer->getSize() / sizeof(unsigned int); }

			inline const BufferObject* const getElementBuffer() const { return mElementBuffer; }

			inline const BufferObject* const getVertexBuffer() const { return mVertexBuffer; }
		};

	}
}
