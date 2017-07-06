#include "Vector3f.h"

namespace engine {
	namespace math {

		Vector3f::Vector3f(fl32 xx, fl32 yy, fl32 zz) {
			x = xx;
			y = yy;
			z = zz;
		}

		Vector3f::Vector3f(const Vector3f& vector) {
			x = vector.x;
			y = vector.y;
			z = vector.z;
		}

		Vector3f Vector3f::normalize() const {
			Vector3f out;
			fl32 length = magnitude();

			out.x = x / length;
			out.y = y / length;
			out.z = z / length;
			return out;
		}

		fl32 Vector3f::magnitude() const {
			return (fl32) sqrt(x * x + y * y + z * z);
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

		Vector3f Vector3f::multiply(fl32 scalar) const {
			Vector3f out;

			out.x = x * scalar;
			out.y = y * scalar;
			out.z = z * scalar;
			return out;
		}

		Vector3f Vector3f::divide(fl32 divider) const {
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

		fl32 Vector3f::dot(const Vector3f& other) const {
			return (x * other.x) + (y * other.y) + (x * other.x);
		}

		Vector3f operator+(Vector3f& a, Vector3f& b) {
			return a.add(b);
		}

		Vector3f operator-(const Vector3f& a, const Vector3f& b) {
			return a.substract(b);
		}

		Vector3f operator*(Vector3f& a, fl32 scalar) {
			return a.multiply(scalar);
		}

		Vector3f operator/(Vector3f& vector, fl32 divider) {
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