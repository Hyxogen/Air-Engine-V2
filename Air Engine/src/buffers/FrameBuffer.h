#pragma once
#include <glad\glad.h>
#include "Texture.h"
#include "RenderBuffer.h"
#include "..\math\Vector4f.h"

namespace engine { namespace buffer {

		struct FrameBuffer : public Buffer {
		public:
			FrameBuffer();

			~FrameBuffer();

			void bind() const;

			void unBind() const;

			virtual void bindTarget(uint32 target) const;

			virtual void unBindTarget(uint32 target) const;

			bool isComplete() const;

			void addTextureBuffer(const Texture* texture, uint32 target) const;

			void addRenderBuffer(const RenderBuffer* renderBuffer, uint32 target) const;

			void blitBuffer(math::Vector4f srcBounds, math::Vector4f dstBounds, uint32 target, uint32 filter = GL_NEAREST);
		};

} }