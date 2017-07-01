#include "Vector2f.h"

namespace engine {
	namespace math {

		Vector2f::Vector2f(float xx, float yy) {
			x = xx;
			y = yy;
		}

		Vector2f::Vector2f(Vector2f& vector) {
			x = vector.x;
			y = vector.y;
		}

		Vector2f Vector2f::normalize() const {
			
			float length = magnitude();

			float xx = x / length;
			float yy = y / length;
			return Vector2f(xx, yy);
		}

		float Vector2f::magnitude() const {
			return (float) sqrt((x * x) + (y * y));
		}

		Vector2f Vector2f::invert() const {
			return Vector2f(-x, -y);
		}

		Vector2f Vector2f::add(const Vector2f& other) const {
			Vector2f out;

			out.x = x + other.x;
			out.y = y + other.y;
			return out;
		}

		Vector2f Vector2f::substract(const Vector2f& other) const {
			return add(other.invert());
		}

		Vector2f Vector2f::multiply(float scalar) const {
			Vector2f out;

			out.x = x * scalar;
			out.y = y * scalar;
			return out;
		}

		Vector2f Vector2f::divide(float divider) const {
			Vector2f out;

			out.x = x / divider;
			out.y = y / divider;
			return out;
		}

		float Vector2f::dot(const Vector2f& other) const {
			return (x * other.x) + (y * other.y);
		}

		Vector2f operator+(Vector2f& a, Vector2f& b) {
			return a.add(b);
		}

		Vector2f operator-(Vector2f& a, Vector2f& b) {
			return a.substract(b);
		}

		Vector2f operator*(Vector2f& a, float scalar) {
			return a.multiply(scalar);
		}

		Vector2f operator/(Vector2f& vector, float divider) {
			return vector.divide(divider);
		}

		bool operator<(Vector2f& a, Vector2f& b) {
			return a.magnitude() < b.magnitude();
		}

		bool operator<=(Vector2f& a, Vector2f& b) {
			return a.magnitude() <= b.magnitude();
		}

		bool operator>(Vector2f& a, Vector2f& b) {
			return a.magnitude() > b.magnitude();
		}

		bool operator>=(Vector2f& a, Vector2f& b) {
			return a.magnitude() >= b.magnitude();
		}
} }