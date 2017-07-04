#pragma once
#include <string>
#include <vector>
#include <glad\glad.h>
#include <sstream>
#include <assimp\scene.h>
#include "..\math\Vector3f.h"
#include "..\math\Vector2f.h"
#include "..\graphics\shader\Shader.h"
#include "..\buffers\Texture.h"

namespace engine {
	namespace geometry {

		struct MeshTexture {
			buffer::Texture* texture;
			std::string type;
			aiString path;

			~MeshTexture();
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
			std::vector<MeshTexture*> mTextures;

			GLuint mVAO, mVBO, mEBO;

		public:
			GLuint indicesCount = 0;

			Mesh(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, const std::vector<MeshTexture*> textures);

			~Mesh();

			void draw(graphics::Shader& shader) const;

			void drawInstanced(graphics::Shader& shader, unsigned int count) const;

			inline GLuint getVaoID() const { return mVAO; }

			inline GLuint getVboID() const { return mVBO; }

			inline GLuint getEboID() const { return mEBO; }
		private:
			void setupMesh();
		};
	}
}