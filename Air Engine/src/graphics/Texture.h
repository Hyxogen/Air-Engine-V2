#pragma once
#include <glad\glad.h>
#include <iostream>
#include <stb_image.h>

namespace engine {
	namespace graphics {

		class Texture{

			GLuint mTextureID;
			int mWidth, mHeight, mColorChannels;
			std::string mPath;

		public:
			Texture(const char* path);
			
			~Texture();

			inline GLuint getTextureID() { return mTextureID; }

			inline unsigned int getWidth() { return mWidth; }

			inline unsigned int getHeight() { return mHeight; }
		};

} }