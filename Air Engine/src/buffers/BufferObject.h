#pragma once
#include <glad\glad.h>
#include <iostream>
#include "Buffer.h"

namespace engine {
	namespace buffer {

		struct BufferObject : public Buffer {
		private:
			uint32 mUsage, mSize;

		public:
			BufferObject(uint32 type, const void* data, unsigned int size, uint32 usage = GL_STATIC_DRAW);

			~BufferObject();

			void bind() const;

			void unBind() const;

			void writeData(const void* data, uint32 size, uint32 offset = 0);

			void* mapBuffer(uint32 action);

			void unMapBuffer() const;

			inline uint32 getSize() const { return mSize; }
		};

} }