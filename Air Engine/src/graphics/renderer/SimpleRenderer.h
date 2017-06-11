#pragma once
#include <glad\glad.h>
#include "..\..\buffers\VertexArray.h"

namespace engine {
	namespace renderer {

		class SimpleRenderer {

		public:
			SimpleRenderer();

			void prepareRender() const;

			void render(const buffer::VertexArray* vao) const;
		};

} }