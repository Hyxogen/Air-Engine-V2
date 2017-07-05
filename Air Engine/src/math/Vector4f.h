#pragma once
#include <math.h>
#include "Matrix4f.h"
#include "..\DataTypes.h"

namespace engine {
	namespace math {

		struct Matrix4f;

		struct Vector4f {

			union {
				struct {
					fl32 x, y, z, w;
				};

				fl32 mPoints[4];
			};

			Vector4f(fl32 xx = 0.0f, fl32 yy = 0.0f, fl32 zz = 0.0f, fl32 ww = 0.0f);

			Vector4f(Vector4f& vector);

			Vector4f invert() const;

			Vector4f add(const Vector4f& other) const;

			Vector4f substract(const Vector4f& other) const;

			Vector4f multiply(fl32 scalar) const;

			Vector4f multiply(const Matrix4f& matrix) const;

			Vector4f divide(fl32 divider) const;

			Vector4f operator-();

			//TODO add assignment operator
			Vector4f operator=(Vector4f&& vector);

			friend Vector4f operator+(Vector4f& a, Vector4f& b);

			friend Vector4f operator-(Vector4f& a, Vector4f& b);

			friend Vector4f operator*(Vector4f& vector, fl32 scalar);

			friend Vector4f operator/(Vector4f& vector, fl32 divider);
		};
	}
}