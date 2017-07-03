#include "RenderBuffer.h"

namespace engine {
	namespace buffer {

		RenderBuffer::RenderBuffer(GLenum storage, unsigned int width, unsigned int height) {
			glGenRenderbuffers(1, &mRenderBufferID);
			glBindRenderbuffer(GL_RENDERBUFFER, mRenderBufferID);

			glRenderbufferStorage(GL_RENDERBUFFER, storage, width, height);

			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}

		RenderBuffer::~RenderBuffer() {
			glDeleteRenderbuffers(1, &mRenderBufferID);
		}

		void RenderBuffer::bind() const {
			glBindRenderbuffer(GL_RENDERBUFFER, mRenderBufferID);
		}

		void RenderBuffer::unBind() const {
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}
} }