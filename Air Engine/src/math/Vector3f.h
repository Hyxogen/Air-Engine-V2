#pragma once
#include <math.h>
#include "..\DataTypes.h"

namespace engine {
	namespace math {

		struct Vector3f {

			union {
				struct {
					fl32 x, y, z;
				};

				fl32 mPoints[3];
			};

			Vector3f(fl32 xx = 0.0f, fl32 yy = 0.0f, fl32 zz = 0.0f);

			Vector3f(Vector3f& vector);

			Vector3f normalize() const;

			fl32 magnitude() const;

			Vector3f invert() const;

			Vector3f add(const Vector3f& other) const;

			Vector3f substract(const Vector3f& other) const;

			Vector3f multiply(fl32 scalar) const;

			Vector3f divide(fl32 divider) const;

			Vector3f cross(const Vector3f& other) const;

			fl32 dot(const Vector3f& other) const;

			Vector3f operator-();

			//Vector3f operator=(Vector3f&& vector);

			friend Vector3f operator+(Vector3f& a, Vector3f& b);

			friend Vector3f operator-(Vector3f& a, Vector3f& b);

			friend Vector3f operator*(Vector3f& vector, fl32 scalar);

			friend Vector3f operator/(Vector3f& vector, fl32 divider);

			friend bool operator<(Vector3f& a, Vector3f& b);

			friend bool operator<=(Vector3f a, Vector3f& b);

			friend bool operator>(Vector3f& a, Vector3f& b);

			friend bool operator>=(Vector3f& a, Vector3f& b);
		};
	}
}