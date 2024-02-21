#pragma once

#include "core.h"
#include <array>

namespace Tosh
{

template <class T, size_t dim = DIM3>
class Point
{
private:
	std::array<T, dim> _data{};

public:
	Point() = default;
	Point(const std::array<T, dim>& data) : _data(data) {}

	// Copy constructor
	Point(const Point<T, dim>& other) : _data(other._data) {}

	// Move constructor
	Point(Point<T, dim>&& other) noexcept : _data(std::move(other._data)) {}

	// Destructor
	~Point() = default;

	// Copy assignment
	Point<T, dim>& operator=(const Point<T, dim>& other)
	{
		_data = other._data;
		return *this;
	}

	// Move assignment
	Point<T, dim>& operator=(Point<T, dim>&& other)
	{
		_data = std::move(other._data);
		return *this;
	}

	// distance from another point
	T distance(const Point<T, dim>& other) const
	{
		T result = 0;
		for (size_t i = 0; i < dim; i++)
		{
			result += SQR(_data[i] - other[i]);
		}
		return sqrt(result);
	}

	// distance squared from another point
	T distanceSquared(const Point<T, dim>& other) const
	{
		T result = 0;
		for (size_t i = 0; i < dim; i++)
		{
			result += SQR(_data[i] - other[i]);
		}
		return result;
	}

	// Operator overloading

	T& operator[](size_t index) { return _data[index]; }
	const T& operator[](size_t index) const { return _data[index]; }

	Point<T, dim> operator+(const Point<T, dim>& other) const
	{
		Point<T, dim> result;
		for (size_t i = 0; i < dim; i++)
		{
			result[i] = _data[i] + other[i];
		}
		return result;
	}

	Point<T, dim> operator-(const Point<T, dim>& other) const
	{
		Point<T, dim> result;
		for (size_t i = 0; i < dim; i++)
		{
			result[i] = _data[i] - other[i];
		}
		return result;
	}

	Point<T, dim> operator*(T scalar) const
	{
		Point<T, dim> result;
		for (size_t i = 0; i < dim; i++)
		{
			result[i] = _data[i] * scalar;
		}
		return result;
	}

	Point<T, dim> operator/(T scalar) const
	{
		Point<T, dim> result;
		for (size_t i = 0; i < dim; i++)
		{
			result[i] = _data[i] / scalar;
		}
		return result;
	}

	Point<T, dim>& operator+=(const Point<T, dim>& other)
	{
		for (size_t i = 0; i < dim; i++)
		{
			_data[i] += other[i];
		}
		return *this;
	}

	Point<T, dim>& operator-=(const Point<T, dim>& other)
	{
		for (size_t i = 0; i < dim; i++)
		{
			_data[i] -= other[i];
		}
		return *this;
	}

	Point<T, dim>& operator*=(T scalar)
	{
		for (size_t i = 0; i < dim; i++)
		{
			_data[i] *= scalar;
		}
		return *this;
	}

	Point<T, dim>& operator/=(T scalar)
	{
		for (size_t i = 0; i < dim; i++)
		{
			_data[i] /= scalar;
		}
		return *this;
	}

	bool operator==(const Point<T, dim>& other) const
	{
		for (size_t i = 0; i < dim; i++)
		{
			if (ABS(_data[i] - other[i]) > EPS)
			{
				return false;
			}
		}
		return true;
	}

	bool operator!=(const Point<T, dim>& other) const
	{
		return !(*this == other);
	}

	Point<T, dim> operator-() const
	{
		Point<T, dim> result;
		for (size_t i = 0; i < dim; i++)
		{
			result[i] = -_data[i];
		}
		return result;
	}
};

typedef Point<float, DIM2> Point2f;
typedef Point<float, DIM3> Point3f;
typedef Point<double, DIM2> Point2d;
typedef Point<double, DIM3> Point3d;
}