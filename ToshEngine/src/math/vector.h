#pragma once
#include "core.h"
#include <array>
#include <gtest/gtest.h>

namespace Tosh {

#define DIM2 2
#define DIM3 3

template <class T, size_t dim = DIM3>
class Vector {
private:
	std::array<T, dim> data{};
public:
	Vector() {}

	Vector(std::array<T, dim>& coord) {
		for (size_t i = 0; i < dim; i++) {
			data[i] = coord[i];
		}
	}

	Vector(T x, T y) {
		static_assert(dim >= DIM2, "Vector dimension mismatch");
		data[0] = x;
		data[1] = y;
	}

	Vector(T x, T y, T z) {
		static_assert(dim >= DIM3, "Vector dimension mismatch");
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	// Copy constructor
	Vector(const Vector<T, dim>& other) {
		for (size_t i = 0; i < dim; i++) {
			data[i] = other[i];
		}
	}

	// Move constructor
	Vector(Vector<T, dim>&& other) noexcept {
		for (size_t i = 0; i < dim; i++) {
			data[i] = std::move(other[i]);
		}
	}

	// Copy assignment
	Vector<T, dim>& operator=(const Vector<T, dim>& other) {
		for (size_t i = 0; i < dim; i++) {
			data[i] = other[i];
		}
		return *this;
	}

	// Move assignment
	Vector<T, dim>& operator=(Vector<T, dim>&& other) {
		for (size_t i = 0; i < dim; i++) {
			data[i] = std::move(other[i]);
		}
		return *this;
	}

	// Destructor
	~Vector() {}

	// Magnitude of the vector
	T magnitude() const {
		T sum = 0;
		for (size_t i = 0; i < dim; i++) {
			sum += data[i] * data[i];
		}
		return sqrt(sum);
	}

	// Magnitude squared of the vector
	T magnitudeSquared() const {
		T sum = 0;
		for (size_t i = 0; i < dim; i++) {
			sum += data[i] * data[i];
		}
		return sum;
	}

	// Normalize the vector
	Vector<T, dim>& normalize() const {
		T mag = magnitude();
		Vector<T, dim> result;
		for (size_t i = 0; i < dim; i++) {
			data[i] = data[i] / mag;
		}
		return *this;
	}

	// Dot product of two vectors
	T dot(const Vector<T, dim>& other) const {
		T sum = 0;
		for (size_t i = 0; i < dim; i++) {
			sum += data[i] * other[i];
		}
		return sum;
	}

	// Cross product of two vectors
	Vector<T, dim> cross(const Vector<T, DIM3>& other) const {
		static_assert(dim >= DIM3, "Cross product is only defined for 3D vectors");
		Vector<T, dim> result;
		result[0] = data[1] * other[2] - data[2] * other[1];
		result[1] = data[2] * other[0] - data[0] * other[2];
		result[2] = data[0] * other[1] - data[1] * other[0];
		return result;
	}

	// Cross product of 2d vectors
	T cross(const Vector<T, DIM2>& other) const {
		static_assert(dim >= DIM2, "Cross product is only defined for 2D vectors");
		return data[0] * other[1] - data[1] * other[0];
	}

	// Distance between two vectors
	T distance(const Vector<T, dim>& other) const {
		T sum = 0;
		for (size_t i = 0; i < dim; i++) {
			sum += (data[i] - other[i]) * (data[i] - other[i]);
		}
		return sqrt(sum);
	}

	// Distance squared between two vectors
	T distanceSquared(const Vector<T, dim>& other) const {
		T sum = 0;
		for (size_t i = 0; i < dim; i++) {
			sum += (data[i] - other[i]) * (data[i] - other[i]);
		}
		return sum;
	}

	// Angle between two vectors
	T angle(const Vector<T, dim>& other) const {
		T dotProduct = dot(other);
		T mag1 = magnitude();
		T mag2 = other.magnitude();
		return acos(dotProduct / (mag1 * mag2));
	}

	// Projection of this vector onto another vector
	Vector<T, dim> project(const Vector<T, dim>& other) const {
		T dotProduct = dot(other);
		T mag = other.magnitudeSquared();
		return other * (dotProduct / mag);
	}

	// Rejection of this vector from another vector
	Vector<T, dim> reject(const Vector<T, dim>& other) const {
		return *this - project(other);
	}

	// Accessors
	T& operator[](size_t index) {
		return data[index];
	}

	const T& operator[](size_t index) const {
		return data[index];
	}

	// Operators
	Vector<T, dim> operator+(const Vector<T, dim>& other) const {
		Vector<T, dim> result;
		for (size_t i = 0; i < dim; i++) {
			result[i] = data[i] + other[i];
		}
		return result;
	}

	// negate the vector
	Vector<T, dim> operator-() const {
		Vector<T, dim> result;
		for (size_t i = 0; i < dim; i++) {
			result[i] = -data[i];
		}
		return result;
	}

	Vector<T, dim> operator-(const Vector<T, dim>& other) const {
		Vector<T, dim> result;
		for (size_t i = 0; i < dim; i++) {
			result[i] = data[i] - other[i];
		}
		return result;
	}

	Vector<T, dim> operator*(const T& scalar) const {
		Vector<T, dim> result;
		for (size_t i = 0; i < dim; i++) {
			result[i] = data[i] * scalar;
		}
		return result;
	}

	Vector<T, dim> operator/(const T& scalar) const {
		Vector<T, dim> result;
		for (size_t i = 0; i < dim; i++) {
			result[i] = data[i] / scalar;
		}
		return result;
	}

	Vector<T, dim>& operator+=(const Vector<T, dim>& other) {
		for (size_t i = 0; i < dim; i++) {
			data[i] += other[i];
		}
		return *this;
	}

	Vector<T, dim>& operator-=(const Vector<T, dim>& other) {
		for (size_t i = 0; i < dim; i++) {
			data[i] -= other[i];
		}
		return *this;
	}

	Vector<T, dim>& operator*=(const T& scalar) {
		for (size_t i = 0; i < dim; i++) {
			data[i] *= scalar;
		}
		return *this;
	}

	Vector<T, dim>& operator/=(const T& scalar) {
		for (size_t i = 0; i < dim; i++) {
			data[i] /= scalar;
		}
		return *this;
	}

	// Comparison operators
	bool operator==(const Vector<T, dim>& other) const {
		for (size_t i = 0; i < dim; i++) {
			if (NOT_EQUAL(data[i],other[i])) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const Vector<T, dim>& other) const {
		return !(*this == other);
	}

	// Print the vector
	friend std::ostream& operator<<(std::ostream& os, const Vector<T, dim>& vec) {
		os << "(";
		for (size_t i = 0; i < dim; i++) {
			os << vec[i];
			if (i < dim - 1) {
				os << ", ";
			}
		}
		os << ")";
		return os;
	}
};

// Usefull typedefs
typedef Vector<float, DIM2> Vec2f;
typedef Vector<float, DIM3> Vec3f;
typedef Vector<double, DIM2> Vec2d;
typedef Vector<double, DIM3> Vec3d;

} // namespace Tosh
