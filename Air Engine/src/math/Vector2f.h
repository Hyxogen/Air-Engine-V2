#pragma once
#include <math.h>

namespace engine {
	namespace math {

		struct Vector2f {

			union {
				struct {
					float x, y;
				};

				float mPoints[2];
			};

			Vector2f(float xx = 0.0f, float yy = 0.0f);

			Vector2f(Vector2f& vector);

			Vector2f normalize() const;

			float magnitude() const;

			Vector2f invert() const;

			Vector2f add(const Vector2f& other) const;

			Vector2f substract(const Vector2f& other) const;

			Vector2f multiply(float scalar) const;

			Vector2f divide(float divider) const;

			float dot(const Vector2f& other) const;

			Vector2f operator-();

			//Vector2f operator=(Vector2f&& vector);

			friend Vector2f operator+(Vector2f& a, Vector2f& b);

			friend Vector2f operator-(Vector2f& a, Vector2f& b);

			friend Vector2f operator*(Vector2f& vector, float scalar);

			friend Vector2f operator/(Vector2f& vector, float divider);

			friend bool operator<(Vector2f& a, Vector2f& b);

			friend bool operator<=(Vector2f a, Vector2f& b);
			
			friend bool operator>(Vector2f& a, Vector2f& b);

			friend bool operator>=(Vector2f& a, Vector2f& b);
		};
} }