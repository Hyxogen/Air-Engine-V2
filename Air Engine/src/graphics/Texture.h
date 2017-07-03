#pragma once
#include <glad\glad.h>
#include <iostream>
#include <stb_image.h>
#include <vector>
#include <string>

namespace engine {
	namespace graphics {

		class Texture{

			GLuint mTextureID;
			int mWidth, mHeight, mColorChannels;
			std::string mPath;

		public:
			Texture(const std::string& path);

			Texture(std::vector<std::string> faces);
			
			~Texture();

			inline GLuint getTextureID() { return mTextureID; }

			inline unsigned int getWidth() { return mWidth; }

			inline unsigned int getHeight() { return mHeight; }
		};

} }