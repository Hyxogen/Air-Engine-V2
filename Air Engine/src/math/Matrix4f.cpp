#include "Matrix4f.h"

namespace engine {
	namespace math {

		Matrix4f::Matrix4f(float diagonal) {
			for (int i = 0; i < 16; i++) {
				mElements[i] = 0.0f;
			}

			mElements[0 + 0 * 4] = diagonal;
			mElements[1 + 1 * 4] = diagonal;
			mElements[2 + 2 * 4] = diagonal;
			mElements[3 + 3 * 4] = diagonal;
		}

		Matrix4f Matrix4f::identity() {
			return Matrix4f(1.0f);
		}

		Matrix4f Matrix4f::multiply(const Matrix4f& other) const {
			Matrix4f out;

			for (int z = 0; z < 4; z++) {
				for (int y = 0; y < 4; y++) {
					for (int x = 0; x < 4; x++) {
						out.mElements[z + y * 4] += mElements[x + z * 4] * other.mElements[y + x * 4];
#ifdef MAT_MUL_DEBUG
						std::cout << "(" << mElements[x + z * 4] << " , " << other.mElements[y + x * 4] << ") + ";
#endif
					}
#ifdef MAT_MUL_DEBUG
					std::cout << " || ";
#endif
				}
#ifdef MAT_MUL_DEBUG
				std::cout << "\n" << std::endl;
#endif
			}

			return out;
		}

		Matrix4f Matrix4f::rotation(const Vector3f& axis, float angle) {
			Matrix4f out(1.0f);

			float s = (float) sin(degToRad(angle));
			float c = (float) cos(degToRad(angle));
			float omc = 1 - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			out.mElements[0 + 0 * 4] = c + x * omc;
			out.mElements[1 + 0 * 4] = x * y * omc;
			out.mElements[3 + 0 * 4] = x * z * omc + y * s;

			out.mElements[0 + 1 * 4] = y * x * omc + z * s;
			out.mElements[1 + 1 * 4] = c + y * omc;
			out.mElements[3 + 1 * 4] = y * z * omc - x * s;

			out.mElements[0 + 2 * 4] = z * x * omc - y * s;
			out.mElements[1 + 2 * 4] = z * y * omc + x * s;
			out.mElements[3 + 2 * 4] = c + z * omc;

			return out;
		}

		Matrix4f Matrix4f::perspective(float ar, float fov, float near, float far) {
			Matrix4f out;
			float tanHalf = (float) tan(degToRad(fov) / 2.0f);

			out.mElements[0 + 0 * 4] = 1.0f / (ar * tanHalf);
			out.mElements[1 + 1 * 4] = 1.0f / tanHalf;

			out.mElements[2 + 2 * 4] = -((far + near) / (far - near));
			out.mElements[2 + 3 * 4] = -((2.0f * far * near) / (far - near));

			out.mElements[3 + 2 * 4] = -1.0f;

			return out;
		}
		
		/*
		Matrix4f Matrix4f::perspective(float aspect, float fov, float near, float far) {
			Matrix4f out(1.0f);
			//If not working use: tanh, instead of: tan
			float tanHalf = (float)tan(fov / 2.0f);

			out.mElements[0 + 0 * 4] = 1.0f / (tanHalf * aspect);
			out.mElements[1 + 1 * 4] = 1.0f / tanHalf;

			out.mElements[2 + 2 * 4] = -(far + near) / (far - near);
			out.mElements[2 + 3 * 4] = -(2.0f * far * near) / (far - near);

			out.mElements[3 + 2 * 4] = -1.0f;
			out.mElements[3 + 3 * 4] = 0.0f;

			return out;
		}
		*/

		Matrix4f Matrix4f::orthographic(float near, float far, float top, float bottom, float left, float right) {
			Matrix4f out(1.0f);

			out.mElements[0 + 0 * 4] = 2.0f / (right - left);
			out.mElements[3 + 0 * 4] = -((right + left) / (right - left));

			out.mElements[1 + 1 * 4] = 2.0f / (top - bottom);
			out.mElements[3 + 1 * 4] = -((top + bottom) / (top - bottom));

			out.mElements[2 + 2 * 4] = -2.0f / (far - near);
			out.mElements[3 + 2 * 4] = -((far + near) / (far - near));
			
			out.mElements[3 + 3 * 4] = 1.0f;

			return out;
		}
		

		Matrix4f Matrix4f::translation(const Vector3f& position) {
			Matrix4f out(1.0f);

			out.mElements[0 + 3 * 4] = position.x;
			out.mElements[1 + 3 * 4] = position.y;
			out.mElements[2 + 3 * 4] = position.z;

			return out;
		}

		Matrix4f Matrix4f::scale(const Vector3f& scale) {
			Matrix4f out(1.0f);

			out.mElements[0 + 0 * 4] = scale.x;
			out.mElements[1 + 1 * 4] = scale.y;
			out.mElements[2 + 2 * 4] = scale.z;

			return out;
		}

		Matrix4f Matrix4f::transformation(const Matrix4f& translation, const Matrix4f& rotation, const Matrix4f& scale) {
			return (scale.multiply(rotation)).multiply(translation);
		}
}}