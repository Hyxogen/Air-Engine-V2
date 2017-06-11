#pragma once
#include <glad/glad.h>
#include <vector>
#include <algorithm>


namespace engine {
	namespace buffer {

		class VertexArray {

			std::vector<float> mData;
			GLuint VAO = 0, VBO = 0, EBO = 0;

		public:
			VertexArray(std::vector<float>&& data);

			~VertexArray();

			void bind() const;
			
			void unBind() const;

			inline const GLuint getVertexID() const { return VAO; }

			inline const std::vector<float>& getData() const { return mData; }

		};

	}
}
