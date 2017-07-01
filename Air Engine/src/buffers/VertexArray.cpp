#include "VertexArray.h"

namespace engine {
	namespace buffer {

		VertexArray::VertexArray(std::vector<float>&& data, std::vector<unsigned int>&& indices) : mData() , mIndices() {
			std::swap(mData, data);
			std::swap(mIndices, indices);

			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, mData.size() * sizeof(GLfloat), mData.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) NULL);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(int), mIndices.data(), GL_STATIC_DRAW);

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