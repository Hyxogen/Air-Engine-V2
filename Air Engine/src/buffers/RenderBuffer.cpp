#include "RenderBuffer.h"

namespace engine {
	namespace buffer {

		RenderBuffer::RenderBuffer(GLenum storage, unsigned int width, unsigned int height) {
			mType = GL_RENDERBUFFER;
			glGenRenderbuffers(1, &mBufferID);

			glBindRenderbuffer(GL_RENDERBUFFER, mBufferID);
			glRenderbufferStorage(GL_RENDERBUFFER, storage, width, height);

			glBindRenderbuffer(GL_RENDERBUFFER, 0);
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