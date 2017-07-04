#pragma once
#include <glad\glad.h>
#include "Buffer.h"

namespace engine { namespace buffer {

		class RenderBuffer : public Buffer {
		public:
			RenderBuffer(GLenum storage, unsigned int width, unsigned int height);

			~RenderBuffer();

			void bind() const;

			void unBind() const;
		};

} }