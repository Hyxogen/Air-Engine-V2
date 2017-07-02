#pragma once
#include <string>
#include <vector>
#include <glad\glad.h>
#include <assimp\scene.h>
#include "..\math\Vector3f.h"
#include "..\math\Vector2f.h"
#include "..\graphics\shader\Shader.h"

namespace engine {
	namespace geometry {

		struct Texture {
			unsigned int id;
			std::string type;
			aiString path;
		};

		struct Vertex {
			math::Vector3f mVertex, mNormal;
			math::Vector2f mTexCoord;

			Vertex(const Vertex& vertex);
			Vertex();
		};

		class Mesh {

			std::vector<Vertex> mVertices;
			std::vector<unsigned int> mIndices;
			std::vector<Texture> mTextures;

			GLuint mVAO, mVBO, mEBO;

		public:
			Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);

			~Mesh();

			void draw(graphics::Shader shader) const;
		private:
			void setupMesh();
		};
	}
}