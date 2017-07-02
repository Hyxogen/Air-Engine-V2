#include "Mesh.h"

namespace engine {
	namespace geometry {

		Vertex::Vertex(const Vertex& vertex) {
			mVertex = vertex.mVertex;
			mNormal = vertex.mNormal;
			mTexCoord = vertex.mTexCoord;
		}

		Vertex::Vertex() {
			mVertex = math::Vector3f();
			mNormal = math::Vector3f();
			mTexCoord = math::Vector2f();
		}

		Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures) {
			mVertices = vertices;
			mIndices = indices;
			mTextures = textures;
			//TODO check if vector ins't null
			setupMesh();
		}

		Mesh::~Mesh() {
			glDeleteVertexArrays(1, &mVAO);
			glDeleteBuffers(1, &mVBO);
			glDeleteBuffers(1, &mEBO);
		}

		void Mesh::setupMesh() {
			glGenVertexArrays(1, &mVAO);
			glGenBuffers(1, &mVBO);
			glGenBuffers(1, &mEBO);

			glBindVertexArray(mVAO);

			glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), (void*)&mVertices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));
			
			glEnableVertexAttribArray(2); 
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mTexCoord));

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
			//If not working use void cast on: vector[0] everywhere
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), (void*)&mIndices[0], GL_STATIC_DRAW);

			glBindVertexArray(0);
		}

		void Mesh::draw(graphics::Shader shader) const {

#ifdef TEXTURE_RENDER
			unsigned int diffuseTexCount = 1;
			unsigned int specularTexCount = 1;

			for (int i = 0; i < mTextures.size(); i++) {
				std::string name, number;

				name = mTextures[i].type;

				if(name == "texture_diffuse")
					number = std::to_string(diffuseTexCount++);
				else if(name == "texture_specular")
					number = std::to_string(specularTexCount++);

				glActiveTexture(GL_TEXTURE0 + i);
				shader.setFloat(("material." + name + number).c_str(), i);
				glBindTexture(GL_TEXTURE_2D, mTextures[i].id);
			}
			glActiveTexture(GL_TEXTURE0);
#endif

			glBindVertexArray(mVAO);
			glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
}