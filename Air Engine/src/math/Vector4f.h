#pragma once
#include <math.h>
#include "Matrix4f.h"

namespace engine {
	namespace math {

		struct Matrix4f;

		struct Vector4f {

			union {
				struct {
					float x, y, z, w;
				};

				float mPoints[4];
			};

			Vector4f(float xx = 0.0f, float yy = 0.0f, float zz = 0.0f, float ww = 0.0f);

			Vector4f(Vector4f& vector);

			Vector4f invert() const;

			Vector4f add(const Vector4f& other) const;

			Vector4f substract(const Vector4f& other) const;

			Vector4f multiply(float scalar) const;

			Vector4f multiply(const Matrix4f& matrix) const;

			Vector4f divide(float divider) const;

			Vector4f operator-();

			//TODO add assignment operator
			Vector4f operator=(Vector4f&& vector);

			friend Vector4f operator+(Vector4f& a, Vector4f& b);

			friend Vector4f operator-(Vector4f& a, Vector4f& b);

			friend Vector4f operator*(Vector4f& vector, float scalar);

			friend Vector4f operator/(Vector4f& vector, float divider);
		};
	}
}