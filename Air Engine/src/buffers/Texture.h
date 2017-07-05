#pragma once
#include <glad\glad.h>
#include <iostream>
#include <stb_image.h>
#include <vector>
#include <string>
#include "Buffer.h"

namespace engine { namespace buffer {

		class Texture : public Buffer {

			int mWidth, mHeight, mColorChannels;
			std::string mPath;

		public:
			Texture(unsigned int width, unsigned int height, uint32 target = GL_TEXTURE_2D, uint32 colorChannels = GL_RGB,
				const void* data = NULL);

			Texture(unsigned int width, unsigned int height, short numSamples);

			Texture(const std::string& path);

			Texture(std::vector<std::string> faces);
			
			~Texture();

			void bind() const;

			void unBind() const;

			void setTextureParamI(uint32 param, uint32 value);

			inline unsigned int getWidth() const { return mWidth; }

			inline unsigned int getHeight() const { return mHeight; }
		};

} }