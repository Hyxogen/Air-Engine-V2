#pragma once
#include "Mathf.h"
#include "Vector3f.h"
#include "Vector4f.h"
#include "..\DataTypes.h"

namespace engine {
	namespace math {

		struct Matrix4f {

			union {
				struct {
					fl32 mElements[4 * 4];
				};

				struct {
					fl32 mRows[4][4];
				};
			};

			Matrix4f(fl32 diagonal = 0.0f);

			Matrix4f multiply(const Matrix4f& other) const;

			static Matrix4f identity();

			static Matrix4f orthographic(fl32 near, fl32 far,fl32 top, fl32 bottom, fl32 left, fl32 right);

			static Matrix4f perspective(fl32 ar, fl32 fov, fl32 near, fl32 far);

			static Matrix4f rotation(const Vector3f& axis, fl32 angle);

			static Matrix4f rotation(const Vector3f& r, const Vector3f& u, const Vector3f& f);

			static Matrix4f translation(const Vector3f& position);

			static Matrix4f scale(const Vector3f& scale);

			static Matrix4f transformation(const Matrix4f& translation, const Matrix4f& rotation, const Matrix4f& scale);

			static Matrix4f lookAt(const Vector3f& position, const Vector3f& center, const Vector3f& up);

			friend Matrix4f operator*(const Matrix4f& a, const Matrix4f& b);
		};

	}
}