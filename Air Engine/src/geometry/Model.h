#pragma once
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include "Mesh.h"

namespace engine {
	namespace geometry {

		class Model {
			std::vector<Mesh> mMeshes;
			std::vector<Texture> mLoaded_textures;
			std::string mDirectory;

		public:
			Model(char* path);

			~Model();

			void draw(graphics::Shader shader) const;
		private:
			void loadModel(std::string path);

			void processNode(aiNode* node, const aiScene* scene);

			Mesh processMesh(aiMesh* mesh, const aiScene* scene);
			
			std::vector<Texture> getTextures(aiMaterial* material, aiTextureType type, std::string typeName);
		};
}}