#pragma once
#include <glad\glad.h>
#include <iostream>
#include "Buffer.h"

namespace engine {
	namespace buffer {

		struct BufferObject : public Buffer {
		private:
			GLenum mUsage, mSize;

		public:
			BufferObject(GLenum type, const void* data, unsigned int size, GLenum usage = GL_STATIC_DRAW);

			~BufferObject();

			void bind() const;

			void unBind() const;

			void writeData(const void* data, GLuint size, GLuint offset = 0);

			void* mapBuffer(GLenum action);

			void unMapBuffer() const;

			inline GLenum getSize() const { return mSize; }
		};

} }