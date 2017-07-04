#include "Model.h"

namespace engine {
	namespace geometry {

		Model::Model(char* path) {
			loadModel(path);
		}

		Model::~Model() {
			for (unsigned int i = 0; i < mMeshes.size(); i++)
				delete mMeshes[i];
			for (unsigned int i = 0; i < mLoaded_textures.size(); i++)
				delete mLoaded_textures[i];
		}

		void Model::loadModel(std::string path) {
			Assimp::Importer importer;

			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_GenNormals);

			if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
				std::cout << importer.GetErrorString() << std::endl;
				return;
			}
			mDirectory = path.substr(0, path.find_last_of('/'));

			processNode(scene->mRootNode, scene);
		}

		void Model::processNode(aiNode* node, const aiScene* scene) {
			for (unsigned int i = 0; i < node->mNumMeshes; i++) {
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				mMeshes.push_back(processMesh(mesh, scene));
			}

			for (unsigned int i = 0; i < node->mNumChildren; i++)
				processNode(node->mChildren[i], scene);
		}

		Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene) {
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			std::vector<MeshTexture*> textures;

			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				Vertex vertex;

				math::Vector3f vector;
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.mVertex = vector;

				math::Vector3f normal;
				normal.x = mesh->mNormals[i].x;
				normal.y = mesh->mNormals[i].y;
				normal.z = mesh->mNormals[i].z;
				vertex.mNormal = normal;

				if (mesh->mTextureCoords[0]) {
					math::Vector2f texCoord;
					texCoord.x = mesh->mTextureCoords[0][i].x;
					texCoord.y = mesh->mTextureCoords[0][i].y;
					vertex.mTexCoord = texCoord;
				}
				else
					vertex.mTexCoord = math::Vector2f();

				vertices.push_back(vertex);
			}

			for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
				aiFace face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}

			if (mesh->mMaterialIndex >= 0) {
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

				std::vector<MeshTexture*> diffuseMaps = getTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
				textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

				std::vector<MeshTexture*> specularMaps = getTextures(material, aiTextureType_SPECULAR, "texture_specular");
				textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			}

			return new Mesh(vertices, indices, textures);
		}

		std::vector<MeshTexture*> Model::getTextures(aiMaterial* material, aiTextureType type, std::string typeName) {
			std::vector<MeshTexture*> textures;
			
			for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
				aiString str;
				material->GetTexture(type, i, &str);
				bool skip = false;
				for (unsigned int j = 0; j < mLoaded_textures.size(); j++) {
					if (std::strcmp(mLoaded_textures[j]->path.C_Str(), str.C_Str()) == 0) {
						textures.push_back(mLoaded_textures[j]);
						skip = true;
						break;
					}
				}
				if (!skip) {
					MeshTexture* texture = new MeshTexture();

					std::string path = mDirectory + "/" + str.C_Str();
					//TODO add texture loading
					texture->texture = new buffer::Texture(path.c_str());
					texture->type = typeName;
					texture->path = str;
					textures.push_back(texture);
					mLoaded_textures.push_back(texture);
				}
			}

			return textures;
		}

		void Model::draw(graphics::Shader& shader) const {
			for (unsigned int i = 0; i < mMeshes.size(); i++)
				mMeshes[i]->draw(shader);
		}

		void Model::drawInstanced(graphics::Shader& shader, unsigned int count) const {
			for (unsigned int i = 0; i < mMeshes.size(); i++)
				mMeshes[i]->drawInstanced(shader, count);
		}
} }