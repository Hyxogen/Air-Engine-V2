#pragma once
#include <math.h>

namespace engine {
	namespace math {

		struct Vector3f {

			union {
				struct {
					float x, y, z;
				};

				float mPoints[3];
			};

			Vector3f(float xx = 0.0f, float yy = 0.0f, float zz = 0.0f);

			Vector3f(Vector3f& vector);

			Vector3f normalize() const;

			const float magnitude() const;

			Vector3f invert() const;

			Vector3f add(const Vector3f& other) const;

			Vector3f substract(const Vector3f& other) const;

			Vector3f multiply(float scalar) const;

			Vector3f divide(float divider) const;

			Vector3f cross(const Vector3f& other) const;

			float dot(const Vector3f& other) const;

			Vector3f operator-();

			Vector3f operator=(Vector3f&& vector);

			friend Vector3f operator+(Vector3f& a, Vector3f& b);

			friend Vector3f operator-(Vector3f& a, Vector3f& b);

			friend Vector3f operator*(Vector3f& vector, float scalar);

			friend Vector3f operator/(Vector3f& vector, float divider);

			friend bool operator<(Vector3f& a, Vector3f& b);

			friend bool operator<=(Vector3f a, Vector3f& b);

			friend bool operator>(Vector3f& a, Vector3f& b);

			friend bool operator>=(Vector3f& a, Vector3f& b);
		};
	}
}