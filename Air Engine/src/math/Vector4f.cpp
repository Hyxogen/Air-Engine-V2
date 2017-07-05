#include "Vector4f.h"
#include <iostream>

namespace engine {
	namespace math {

		Vector4f::Vector4f(fl32 xx, fl32 yy, fl32 zz, fl32 ww) {
			x = xx;
			y = yy;
			z = zz;
			w = ww;
		}

		Vector4f::Vector4f(Vector4f& vector) {
			x = vector.x;
			y = vector.y;
			z = vector.z;
			w = vector.w;
		}


		Vector4f Vector4f::invert() const {
			return Vector4f(-x, -y, -z, -w);
		}

		Vector4f Vector4f::add(const Vector4f& other) const {
			Vector4f out;

			out.x = x + other.x;
			out.y = y + other.y;
			out.z = z + other.z;
			out.w = w + other.w;
			return out;
		}

		Vector4f Vector4f::substract(const Vector4f& other) const {
			return add(other.invert());
		}

		Vector4f Vector4f::multiply(fl32 scalar) const {
			Vector4f out;

			out.x = x * scalar;
			out.y = y * scalar;
			out.z = z * scalar;
			out.w = w * scalar;
			return out;
		}

		Vector4f Vector4f::multiply(const Matrix4f& matrix) const {
			Vector4f out;

			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					out.mPoints[y] += matrix.mElements[x + y * 4] * mPoints[x];
//					std::cout << "(" << matrix.mElements[x + y * 4] << " * " << mPoints[x] << ") +";
				}
//				std::cout << "\n" << std::endl;
			}

			return out;
		}

		Vector4f Vector4f::divide(fl32 divider) const {
			Vector4f out;

			out.x = x / divider;
			out.y = y / divider;
			out.z = z / divider;
			out.w = w / divider;
			return out;
		}

		Vector4f Vector4f::operator-() {
			return invert();
		}

		Vector4f operator+(Vector4f& a, Vector4f& b) {
			return a.add(b);
		}

		Vector4f operator-(Vector4f& a, Vector4f& b) {
			return a.substract(b);
		}

		Vector4f operator*(Vector4f& a, fl32 scalar) {
			return a.multiply(scalar);
		}

		Vector4f operator/(Vector4f& vector, fl32 divider) {
			return vector.divide(divider);
		}
	}
}