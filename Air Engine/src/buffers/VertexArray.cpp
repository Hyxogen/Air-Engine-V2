#include "VertexArray.h"

namespace engine {
	namespace buffer {

		VertexArray::VertexArray(std::vector<float>&& data) {
			std::swap(this->data, data);

			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, this->data.size() * sizeof(GLfloat), this->data.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) NULL);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(VAO);
			
		}

		VertexArray::~VertexArray() {
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
			glDeleteVertexArrays(1, &VAO);
		}

		void VertexArray::Bind() const {
			glBindVertexArray(VAO);
		}

		void VertexArray::UnBind() const {
			glBindVertexArray(0);
		}
	}
}