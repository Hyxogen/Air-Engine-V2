#pragma once
#include <math.h>
#include "..\DataTypes.h"

namespace engine {
	namespace math {

		struct Vector2f {

			union {
				struct {
					fl32 x, y;
				};

				fl32 mPoints[2];
			};

			Vector2f(fl32 xx = 0.0f, fl32 yy = 0.0f);

			Vector2f(Vector2f& vector);

			Vector2f normalize() const;

			fl32 magnitude() const;

			Vector2f invert() const;

			Vector2f add(const Vector2f& other) const;

			Vector2f substract(const Vector2f& other) const;

			Vector2f multiply(fl32 scalar) const;

			Vector2f divide(fl32 divider) const;

			fl32 dot(const Vector2f& other) const;

			Vector2f operator-();

			//Vector2f operator=(Vector2f&& vector);

			friend Vector2f operator+(Vector2f& a, Vector2f& b);

			friend Vector2f operator-(Vector2f& a, Vector2f& b);

			friend Vector2f operator*(Vector2f& vector, fl32 scalar);

			friend Vector2f operator/(Vector2f& vector, fl32 divider);

			friend bool operator<(Vector2f& a, Vector2f& b);

			friend bool operator<=(Vector2f a, Vector2f& b);
			
			friend bool operator>(Vector2f& a, Vector2f& b);

			friend bool operator>=(Vector2f& a, Vector2f& b);
		};
} }