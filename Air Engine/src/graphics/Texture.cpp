#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

namespace engine {
	namespace graphics {

		Texture::Texture(const char* path) {
			unsigned char* data = stbi_load(path, &mWidth, &mHeight, &mColorChannels, 0);
			mPath = path;

			if (data) {
				glGenTextures(1, &mTextureID);
				glBindTexture(GL_TEXTURE_2D, mTextureID);

				GLenum format;
				if (mColorChannels == 1)
					format = GL_RED;
				else if (mColorChannels == 3)
					format = GL_RGB;
				else if (mColorChannels == 4)
					format = GL_RGBA;

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, (GLfloat)-0.4f);

				glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);

				glBindTexture(GL_TEXTURE_2D, 0);
				std::cout << "Loaded texture: " << path << std::endl;
			}
			else
				std::cout << "Could not load texture: " << path << std::endl;
			stbi_image_free(data);
		}

		Texture::~Texture() {
			glDeleteTextures(1, &mTextureID);
			std::cout << "Deleting texture " << mPath.c_str() << std::endl;
		}
} }