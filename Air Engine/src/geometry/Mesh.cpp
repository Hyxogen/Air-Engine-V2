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

		MeshTexture::~MeshTexture() {
			delete texture;
		}

		Mesh::Mesh(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, const std::vector<MeshTexture*> textures) {
			mVertices = vertices;
			mIndices = indices;
			mTextures = textures;
			indicesCount = indices.size();

			//TODO check if vector ins't null
			setupMesh();
		}

		Mesh::~Mesh() {
			std::cout << "Mesh get's deleted" << std::endl;
			delete mVertexArray;
		}

		void Mesh::setupMesh() {
			mVertexArray = new buffer::VertexArray((void*)mVertices.data(), mVertices.size() * sizeof(Vertex), mIndices);

			mVertexArray->getVertexBuffer()->bind();

			mVertexArray->assignAttribPointer(0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
			mVertexArray->assignAttribPointer(1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));
			mVertexArray->assignAttribPointer(2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, mTexCoord));
			
			glBindVertexArray(0);
		}

		void Mesh::draw(graphics::Shader& shader) const {
			
			unsigned int diffuseTexCount = 1;
			unsigned int specularTexCount = 1;

			for (unsigned int i = 0; i < mTextures.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				std::stringstream ss;
				std::string number;
				std::string name = mTextures[i]->type;

				if (name == "texture_diffuse")
					ss << diffuseTexCount++;
				else if (name == "texture_specular")
					ss << specularTexCount++;
				//continue;
			//ss << 
				number = ss.str();

				std::string* combined = new std::string("material." + name + number);

				const char* ccombined = combined->c_str();

				shader.setInt(ccombined, i);
				glBindTexture(GL_TEXTURE_2D, mTextures[i]->texture->getBufferID());
				delete combined;
			}
			

			glBindVertexArray(mVertexArray->getBufferID());
			glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glActiveTexture(GL_TEXTURE0);
		}

		void Mesh::drawInstanced(graphics::Shader& shader, unsigned int count) const {

			unsigned int diffuseTexCount = 1;
			unsigned int specularTexCount = 1;

			for (unsigned int i = 0; i < mTextures.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				std::stringstream ss;
				std::string number;
				std::string name = mTextures[i]->type;

				if (name == "texture_diffuse")
					ss << diffuseTexCount++;
				else if (name == "texture_specular")
					ss << specularTexCount++;
				//continue;
				//ss << 
				number = ss.str();

				std::string* combined = new std::string("material." + name + number);

				const char* ccombined = combined->c_str();

				shader.setInt(ccombined, i);
				glBindTexture(GL_TEXTURE_2D, mTextures[i]->texture->getBufferID());
				delete combined;
			}


			glBindVertexArray(mVertexArray->getBufferID());
			glDrawElementsInstanced(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0, count);
			glBindVertexArray(0);
			glActiveTexture(GL_TEXTURE0);
		}
} }