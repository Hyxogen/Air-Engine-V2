#pragma once
#include <glad\glad.h>
#include "Texture.h"
#include "RenderBuffer.h"

namespace engine {
	namespace buffer {

		struct FrameBuffer {
		private:

			GLuint mFrameBufferID;

		public:
			FrameBuffer();

			~FrameBuffer();

			void bind() const;

			void unBind() const;

			bool isComplete() const;

			void addTextureBuffer(const Texture* texture, GLenum type) const;

			void addRenderBuffer(const RenderBuffer* renderBuffer, GLenum type) const;

			inline GLuint getFrameBufferID() { return mFrameBufferID; }
		};

} }