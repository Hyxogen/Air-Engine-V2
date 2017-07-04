#include "VertexArray.h"

namespace engine {
	namespace buffer {

		VertexArray::VertexArray(std::vector<float>&& data, std::vector<unsigned int>&& indices, int vertexSize) : mData() , mIndices() {
			std::swap(mData, data);
			std::swap(mIndices, indices);

			glGenVertexArrays(1, &mBufferID);
			glBindVertexArray(mBufferID);

			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, mData.size() * sizeof(float), (void*)&mData[0], GL_STATIC_DRAW);
			/*
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void *) NULL);
			*/
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(int), mIndices.data(), GL_STATIC_DRAW);

			glBindVertexArray(mBufferID);
			
		}

		VertexArray::~VertexArray() {
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
			glDeleteVertexArrays(1, &mBufferID);
		}

		void VertexArray::assignAttribPointer(GLuint index, unsigned int size, GLenum dataType, bool normalized, GLuint stride,
			void* offset, const BufferObject* bufferObject) {

			bind();
			if (bufferObject != 0)
				bufferObject->bind();

			if (!isBound(GL_ARRAY_BUFFER)) {
				std::cout << "ERROR: No array buffer currently bound!" << std::endl;
					return;
			}

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, size, dataType, normalized, stride, offset);
		}

		void VertexArray::setAttribDivisor(GLuint index, GLuint value) const {
			bind();
			glVertexAttribDivisor(index, value);
		}

		void VertexArray::bind() const {
			glBindVertexArray(mBufferID);
			boundBuffers[GL_VERTEX_ARRAY] = mBufferID;
		}

		void VertexArray::unBind() const {
			glBindVertexArray(0);
			boundBuffers[GL_VERTEX_ARRAY] = 0;
		}
	}
}