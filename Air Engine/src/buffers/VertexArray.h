#pragma once
#include <glad/glad.h>
#include <vector>
#include <algorithm>


namespace engine {
	namespace buffer {

		struct VertexArray {

			std::vector<float> mData;
			std::vector<unsigned int> mIndices;
			GLuint VAO = 0, VBO = 0, EBO = 0;

		public:
			VertexArray(std::vector<float>&& data, std::vector<unsigned int>&& indices, int vertexSize = 3);

			~VertexArray();

			void bind() const;
			
			void unBind() const;

			inline const GLuint getVertexID() const { return VAO; }

			inline const std::vector<float>& getData() const { return mData; }

			inline const std::vector<unsigned int>& getIndices() const { return mIndices; }
		};

	}
}
