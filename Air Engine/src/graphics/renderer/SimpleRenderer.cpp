#include "SimpleRenderer.h"

namespace engine {
	namespace renderer {

		SimpleRenderer::SimpleRenderer() {

		}

		void SimpleRenderer::prepareRender() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void SimpleRenderer::render(const buffer::VertexArray* vertexArray) const {
			glBindVertexArray(vertexArray->getVertexID());

			glEnableVertexAttribArray(0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glDisableVertexAttribArray(0);

			glBindVertexArray(0);
		}
} }