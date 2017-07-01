#include "Vector3f.h"

namespace engine {
	namespace math {

		Vector3f::Vector3f(float xx, float yy, float zz) {
			x = xx;
			y = yy;
			z = zz;
		}

		Vector3f::Vector3f(Vector3f& vector) {
			x = vector.x;
			y = vector.y;
			z = vector.z;
		}

		Vector3f Vector3f::normalize() const {
			Vector3f out;
			float length = magnitude();

			out.x = x / length;
			out.y = y / length;
			out.z = z / length;
			return out;
		}

		const float Vector3f::magnitude() const {
			return sqrt(((x * x) + (z * z)) + (z + z));
		}

		Vector3f Vector3f::invert() const {
			return Vector3f(-x, -y, -z);
		}

		Vector3f Vector3f::add(const Vector3f& other) const {
			Vector3f out;

			out.x = x + other.x;
			out.y = y + other.y;
			out.z = z + other.z;
			return out;
		}

		Vector3f Vector3f::substract(const Vector3f& other) const {
			return add(other.invert());
		}

		Vector3f Vector3f::multiply(float scalar) const {
			Vector3f out;

			out.x = x * scalar;
			out.y = y * scalar;
			out.z = z * scalar;
			return out;
		}

		Vector3f Vector3f::divide(float divider) const {
			Vector3f out;

			out.x = x / divider;
			out.y = y / divider;
			out.z = z / divider;
			return out;
		}

		Vector3f Vector3f::cross(const Vector3f& other) const {
			Vector3f out;

			out.x = (y * other.z) - (z * other.y);
			out.y = (z * other.x) - (x * other.z);
			out.z = (x * other.y) - (y * other.y);
			return out;
		}

		float Vector3f::dot(const Vector3f& other) const {
			return (x * other.x) + (y * other.y) + (x * other.x);
		}

		Vector3f operator+(Vector3f& a, Vector3f& b) {
			return a.add(b);
		}

		Vector3f operator-(Vector3f& a, Vector3f& b) {
			return a.substract(b);
		}

		Vector3f operator*(Vector3f& a, float scalar) {
			return a.multiply(scalar);
		}

		Vector3f operator/(Vector3f& vector, float divider) {
			return vector.divide(divider);
		}

		bool operator<(Vector3f& a, Vector3f& b) {
			return a.magnitude() < b.magnitude();
		}

		bool operator<=(Vector3f& a, Vector3f& b) {
			return a.magnitude() <= b.magnitude();
		}

		bool operator>(Vector3f& a, Vector3f& b) {
			return a.magnitude() > b.magnitude();
		}

		bool operator>=(Vector3f& a, Vector3f& b) {
			return a.magnitude() >= b.magnitude();
		}
	}
}