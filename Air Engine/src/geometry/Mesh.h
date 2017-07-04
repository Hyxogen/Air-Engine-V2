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
#include "..\buffers\VertexArray.h"

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

			buffer::VertexArray* mVertexArray;

		public:
			GLuint indicesCount = 0;

			Mesh(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, const std::vector<MeshTexture*> textures);

			~Mesh();

			void draw(graphics::Shader& shader) const;

			void drawInstanced(graphics::Shader& shader, unsigned int count) const;

			inline GLuint getVaoID() const { return mVertexArray->getBufferID(); }

			inline GLuint getVboID() const { return mVertexArray->getVertexBuffer()->getBufferID(); }

			inline GLuint getEboID() const { return mVertexArray->getElementBuffer()->getBufferID(); }

			inline buffer::VertexArray* getVertexArray() const { return mVertexArray; }
		private:
			void setupMesh();
		};
	}
}