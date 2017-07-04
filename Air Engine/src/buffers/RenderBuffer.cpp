#include "RenderBuffer.h"

namespace engine {
	namespace buffer {

		RenderBuffer::RenderBuffer(unsigned int width, unsigned int height, uint32 storage) {
			mType = GL_RENDERBUFFER;
			glGenRenderbuffers(1, &mBufferID);

			bind();
			glRenderbufferStorage(GL_RENDERBUFFER, storage, width, height);
		}

		RenderBuffer::RenderBuffer(unsigned int width, unsigned int height, unsigned int samples, uint32 storage) {
			mType = GL_RENDERBUFFER;
			glGenRenderbuffers(1, &mBufferID);
			bind();

			glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, storage, width, height);
		}

		RenderBuffer::~RenderBuffer() {
			glDeleteRenderbuffers(1, &mBufferID);
		}

		void RenderBuffer::bind() const {
			glBindRenderbuffer(mType, mBufferID);
			boundBuffers[mType] = mBufferID;
		}

		void RenderBuffer::unBind() const {
			glBindRenderbuffer(mType, 0);
			boundBuffers[mType] = 0;
		}
} }