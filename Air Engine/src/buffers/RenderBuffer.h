#pragma once
#include <glad\glad.h>

namespace engine {
	namespace buffer {

		struct RenderBuffer {
		private:
			GLuint mRenderBufferID;


		public:
			RenderBuffer(GLenum storage, unsigned int width, unsigned int height);

			~RenderBuffer();

			void bind() const;

			void unBind() const;

			inline GLuint getRenderBufferID() const { return mRenderBufferID; }
		};

} }