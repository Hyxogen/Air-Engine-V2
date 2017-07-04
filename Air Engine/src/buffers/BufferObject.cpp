#include "BufferObject.h"

namespace engine {
	namespace buffer {

		BufferObject::BufferObject(GLenum type, const void* data, unsigned int size, GLenum usage) {
			mType = type;
			mUsage = usage;
			mSize = size;

			glGenBuffers(1, &mBufferID);
			glBindBuffer(type, mBufferID);

			glBufferData(type, size, data, usage);
		}

		void BufferObject::bind() const {
			glBindBuffer(mType, mBufferID);
		}

		void BufferObject::unBind() const {
			glBindBuffer(mType, 0);
		}

		void BufferObject::writeData(const void* data, GLuint size, GLuint offset) {
			if (mUsage = GL_STATIC_DRAW)
				std::cout << "WARNING: writing to a buffer with GL_STATIC_DRAW is highly discouraged please use GL_DYNAMIC DRAW instead" 
				<< std::endl;
			bind();
			glBufferSubData(mType, offset, size, data);
		}

		void* BufferObject::mapBuffer(GLenum action) {
			bind();
			return glMapBuffer(mType, action);
		}

		void BufferObject::unMapBuffer() const {
			bind();
			glUnmapBuffer(mType);
		}
} }