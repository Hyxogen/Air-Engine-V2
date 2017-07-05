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
		
		void FrameBuffer::bindTarget(uint32 target) const {
			glBindFramebuffer(target, mBufferID);
			boundBuffers[target] = mBufferID;
		}

		//TODO auto detect target
		void FrameBuffer::unBindTarget(uint32 target) const {
			glBindFramebuffer(target, 0);
			boundBuffers[target] = 0;
		}

		void FrameBuffer::addTextureBuffer(const Texture* texture, uint32 target) const {
			bind();
			//glDrawBuffer(target);
			texture->bind();
			glFramebufferTexture2D(GL_FRAMEBUFFER, target, texture->getType(), texture->getBufferID(), 0);
		}

		void FrameBuffer::addRenderBuffer(const RenderBuffer* renderBuffer, uint32 type) const {
			bind();
			renderBuffer->bind();
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, type, GL_RENDERBUFFER, renderBuffer->getBufferID());
		}

		void FrameBuffer::blitBuffer(math::Vector4f srcBounds, math::Vector4f dstBounds, uint32 target, uint32 filter) {
			glBlitFramebuffer(srcBounds.x, srcBounds.y, srcBounds.z, srcBounds.w, dstBounds.x, dstBounds.y, dstBounds.z, dstBounds.w,
				target, filter);
		}

		bool FrameBuffer::isComplete() const {
			bind();
			return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}

		void FrameBuffer::removeColorBuffer() {
			bind();
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
		}
} }