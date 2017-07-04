#pragma once
#include <glad\glad.h>
#include "Buffer.h"

namespace engine { namespace buffer {

		class RenderBuffer : public Buffer {
		public:
			RenderBuffer(unsigned int width, unsigned int height, uint32 storage);

			RenderBuffer(unsigned int width, unsigned int height, unsigned int samples, uint32 storage);

			~RenderBuffer();

			void bind() const;

			void unBind() const;
		};

} }