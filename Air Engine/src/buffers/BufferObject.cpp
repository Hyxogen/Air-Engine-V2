#include "BufferObject.h"

namespace engine {
	namespace buffer {

		BufferObject::BufferObject(uint32 type, const void* data, unsigned int size, uint32 usage) {
			mType = type;
			mUsage = usage;
			mSize = size;

			glGenBuffers(1, &mBufferID);
			glBindBuffer(type, mBufferID);

			glBufferData(type, size, data, usage);
		}

		BufferObject::~BufferObject() {
			glDeleteBuffers(1, &mBufferID);
		}

		void BufferObject::bind() const {
			glBindBuffer(mType, mBufferID);
			boundBuffers[mType] = mBufferID;
		}

		void BufferObject::unBind() const {
			glBindBuffer(mType, 0);
			boundBuffers[mType] = 0;
		}

		void BufferObject::writeData(const void* data, uint32 size, uint32 offset) {
			if (mUsage = GL_STATIC_DRAW)
				std::cout << "WARNING: writing to a buffer with GL_STATIC_DRAW is highly discouraged please use GL_DYNAMIC DRAW instead" 
				<< std::endl;

			//TODO bind check
			bind();
			glBufferSubData(mType, offset, size, data);
		}

		void* BufferObject::mapBuffer(uint32 action) {
			bind();
			return glMapBuffer(mType, action);
		}

		void BufferObject::unMapBuffer() const {
			bind();
			glUnmapBuffer(mType);
		}
} }