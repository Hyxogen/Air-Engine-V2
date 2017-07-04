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
			Texture(unsigned int width, unsigned int height, GLenum target = GL_TEXTURE_2D, GLenum colorChannels = GL_RGB);

			Texture(const std::string& path);

			Texture(std::vector<std::string> faces);
			
			~Texture();

			void bind() const;

			void unBind() const;

			inline unsigned int getWidth() const { return mWidth; }

			inline unsigned int getHeight() const { return mHeight; }
		};

} }