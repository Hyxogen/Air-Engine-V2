#pragma once
#include <glad\glad.h>
#include "Texture.h"
#include "RenderBuffer.h"

namespace engine { namespace buffer {

		struct FrameBuffer : public Buffer {
		public:
			FrameBuffer();

			~FrameBuffer();

			void bind() const;

			void unBind() const;

			bool isComplete() const;

			void addTextureBuffer(const Texture* texture, GLenum type) const;

			void addRenderBuffer(const RenderBuffer* renderBuffer, GLenum type) const;
		};

} }