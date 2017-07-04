#pragma once
#include <glad\glad.h>
#include <iostream>

namespace engine {
	namespace buffer {

		struct BufferObject {
		private:
			GLuint mBufferID;
			GLenum mType, mUsage, mSize;

		public:
			BufferObject(GLenum type, const void* data, unsigned int size, GLenum usage = GL_STATIC_DRAW);

			~BufferObject();

			void bind() const;

			void unBind() const;

			void writeData(const void* data, GLuint size, GLuint offset = 0);

			void* mapBuffer(GLenum action);

			void unMapBuffer() const;

			inline GLuint getBufferID() const { return mBufferID; }

			inline GLenum getType() const { return mType; }

			inline GLenum getSize() const { return mSize; }
		};

} }