#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

namespace engine { namespace buffer {

		//TODO add standard format like: uint32 etc.
		Texture::Texture(unsigned int width, unsigned int height, GLenum target, GLenum colorChannels) {
			mWidth = width;
			mHeight = height;
			mType = target;

			if (colorChannels == GL_RED)
				mColorChannels = 1;
			if (colorChannels == GL_RGB)
				mColorChannels = 3;
			if (colorChannels == GL_RGBA)
				mColorChannels = 4;

			glGenTextures(1, &mBufferID);
			glBindTexture(GL_TEXTURE_2D, mBufferID);
			glTexImage2D(target, 0, colorChannels, width, height, 0, colorChannels, GL_UNSIGNED_BYTE, NULL);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		Texture::Texture(const std::string& path) {
			unsigned char* data = stbi_load(path.c_str(), &mWidth, &mHeight, &mColorChannels, 0);
			mPath = path;
			mType = GL_TEXTURE_2D;

			if (data) {
				glGenTextures(1, &mBufferID);
				glBindTexture(GL_TEXTURE_2D, mBufferID);

				GLenum format = 0;
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

		Texture::Texture(std::vector<std::string> faces) {
			glGenTextures(1, &mBufferID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, mBufferID);

			mType = GL_TEXTURE_CUBE_MAP;

			GLenum format = 0;
			for (unsigned int i = 0; i < faces.size(); i++) {
				unsigned char* data = stbi_load(faces[i].c_str(), &mWidth, &mHeight, &mColorChannels, 0);

				if (mColorChannels == 1)
					format = GL_RED;
				else if (mColorChannels == 3)
					format = GL_RGB;
				else if (mColorChannels == 4)
					format = GL_RGBA;

				if (data) {
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
					std::cout << "Loaded texture: " << faces[i] << std::endl;
				} else {
					std::cout << "Failed to load cubemap texture at path " << faces[i] << std::endl;
					stbi_image_free(data);
				}
			}

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		Texture::~Texture() {
			glDeleteTextures(1, &mBufferID);
			std::cout << "Deleting texture " << mPath.c_str() << std::endl;
		}

		void Texture::bind() const {
			glBindTexture(mType, mBufferID);
			boundBuffers[mType] = mBufferID;
		}

		void Texture::unBind() const{
			glBindTexture(mType, 0);
			boundBuffers[mType] = 0;
		}
} }