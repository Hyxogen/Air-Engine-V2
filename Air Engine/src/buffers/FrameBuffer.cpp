#include "FrameBuffer.h"

namespace engine {
	namespace buffer {

		FrameBuffer::FrameBuffer() {
			glGenFramebuffers(1, &mFrameBufferID);
		}

		FrameBuffer::~FrameBuffer() {
			glDeleteFramebuffers(1, &mFrameBufferID);
		}

		void FrameBuffer::bind() const {
			glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferID);
		}

		void FrameBuffer::unBind() const {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		//TODO add own types(targets etc)
		void FrameBuffer::addTextureBuffer(const graphics::Texture* texture, GLenum target) const {
			bind();
			texture->bind();
			glFramebufferTexture2D(GL_FRAMEBUFFER, target, GL_TEXTURE_2D, texture->getTextureID(), 0);
		}

		void FrameBuffer::addRenderBuffer(const RenderBuffer* renderBuffer, GLenum type) const {
			bind();
			renderBuffer->bind();
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, type, GL_RENDERBUFFER, renderBuffer->getRenderBufferID());
		}

		bool FrameBuffer::isComplete() const {
			bind();
			std::cout << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
			return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}
} }