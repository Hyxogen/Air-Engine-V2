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
			glDrawElements(GL_TRIANGLES, vertexArray->getIndices().size(), GL_UNSIGNED_INT, 0);
			glDisableVertexAttribArray(0);

			glBindVertexArray(0);
		}
} }