#pragma once
#include "Mathf.h"
#include "Vector3f.h"
#include "Vector4f.h"
#ifdef MAT_MUL_DEBUG
#include <iostream>
#endif

namespace engine {
	namespace math {

		struct Matrix4f {

			union {
				struct {
					float mElements[4 * 4];
				};

				struct {
					float mRows[4][4];
				};
			};

			Matrix4f(float diagonal = 0.0f);

			Matrix4f multiply(const Matrix4f& other) const;

			static Matrix4f identity();

			static Matrix4f orthographic(float near, float far,float top, float bottom, float left, float right);

			static Matrix4f perspective(float ar, float fov, float near, float far);

			static Matrix4f rotation(const Vector3f& axis, float angle);

			static Matrix4f translation(const Vector3f& position);

			static Matrix4f scale(const Vector3f& scale);

			static Matrix4f transformation(const Matrix4f& translation, const Matrix4f& rotation, const Matrix4f& scale);

			friend Matrix4f operator*(const Matrix4f& a, const Matrix4f& b);
		};

	}
}