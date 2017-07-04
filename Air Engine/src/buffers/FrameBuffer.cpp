#include "FrameBuffer.h"

namespace engine {
	namespace buffer {

		FrameBuffer::FrameBuffer() {
			mType = GL_FRAMEBUFFER;
			glGenFramebuffers(1, &mBufferID);
		}

		FrameBuffer::~FrameBuffer() {
			glDeleteFramebuffers(1, &mBufferID);
		}

		void FrameBuffer::bind() const {
			glBindFramebuffer(mType, mBufferID);
			boundBuffers[mType] = mBufferID;
		}

		//TODO add own types(targets etc)
		void FrameBuffer::unBind() const {
			glBindFramebuffer(mType, 0);
			boundBuffers[mType] = 0;
		}
			
		void FrameBuffer::addTextureBuffer(const Texture* texture, GLenum target) const {
			bind();
			//glDrawBuffer(target);
			texture->bind();
			glFramebufferTexture2D(GL_FRAMEBUFFER, target, GL_TEXTURE_2D, texture->getBufferID(), 0);
		}

		void FrameBuffer::addRenderBuffer(const RenderBuffer* renderBuffer, GLenum type) const {
			bind();
			renderBuffer->bind();
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, type, GL_RENDERBUFFER, renderBuffer->getBufferID());
		}

		bool FrameBuffer::isComplete() const {
			bind();
			return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}
} }