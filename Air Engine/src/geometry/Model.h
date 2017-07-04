#pragma once
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include "Mesh.h"
#include "..\buffers\Texture.h"

namespace engine {
	namespace geometry {

		class Model {
			std::vector<MeshTexture*> mLoaded_textures;
			std::string mDirectory;

		public:
			std::vector<Mesh*> mMeshes;

			Model(char* path);

			~Model();

			void draw(graphics::Shader& shader) const;

			void drawInstanced(graphics::Shader& shader, unsigned int count) const;
		private:
			void loadModel(std::string path);

			void processNode(aiNode* node, const aiScene* scene);

			Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
			
			std::vector<MeshTexture*> getTextures(aiMaterial* material, aiTextureType type, std::string typeName);
		};
}}