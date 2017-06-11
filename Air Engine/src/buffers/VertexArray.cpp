#include "VertexArray.h"

namespace engine {
	namespace buffer {

		VertexArray::VertexArray(std::vector<float>&& data) : mData() {
			std::swap(mData, data);

			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, mData.size() * sizeof(GLfloat), mData.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) NULL);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(VAO);
			
		}

		VertexArray::~VertexArray() {
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
			glDeleteVertexArrays(1, &VAO);
		}

		void VertexArray::bind() const {
			glBindVertexArray(VAO);
		}

		void VertexArray::unBind() const {
			glBindVertexArray(0);
		}
	}
}