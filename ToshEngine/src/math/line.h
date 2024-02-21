#pragma once

#include "core.h"

namespace Tosh
{

	// Forward declarations
	class Point;
	class Vector;

	// Template class for representing a line in n-dimensional space
	template <class T, size_t dim = DIM3>
	class Line
	{
	private:
		Point<T,dim> _start; // The starting point of the line
		Point<T, dim> _end; // The ending point of the line

	public:
		// Default constructor
		Line() = default;

		// Constructor with start and end points
		Line(const Point<T, dim>& start, const Point<T, dim>& end) : _start(start), _end(end) {}

		// Copy constructor
		Line(const Line<T, dim>& other) : _start(other._start), _end(other._end) {}

		// Move constructor
		Line(Line<T, dim>&& other) noexcept : _start(std::move(other._start)), _end(std::move(other._end)) {}

		// Destructor
		~Line() = default;

		// Copy assignment operator
		Line<T, dim>& operator=(const Line<T, dim>& other)
		{
			_start = other._start;
			_end = other._end;
			return *this;
		}

		// Move assignment operator
		Line<T, dim>& operator=(Line<T, dim>&& other)
		{
			_start = std::move(other._start);
			_end = std::move(other._end);
			return *this;
		}

		// Get the starting point of the line
		Point<T, dim> start() const { return _start; }

		// Get the ending point of the line
		Point<T, dim> end() const { return _end; }

		// Calculate the length of the line
		T length() const
		{
			T result = 0;
			for (size_t i = 0; i < dim; i++)
			{
				result += SQR(_start[i] - _end[i]);
			}
			return sqrt(result);
		}

		// Calculate the squared length of the line
		T lengthSquared() const
		{
			T result = 0;
			for (size_t i = 0; i < dim; i++)
			{
				result += SQR(_start[i] - _end[i]);
			}
			return result;
		}

		// Linearly interpolate between the start and end points of the line
		Point<T, dim> lerp(T t) const
		{
			Point<T, dim> result;
			for (size_t i = 0; i < dim; i++)
			{
				result[i] = LERP(_start[i], _end[i], t);
			}
			return result;
		}

		// Get the closest point on the line to a given point
		Point<T, dim> closestPoint(const Point<T, dim>& point) const
		{
			Point<T, dim> result;
			T t = 0;
			for (size_t i = 0; i < dim; i++)
			{
				t += (_end[i] - _start[i]) * (point[i] - _start[i]);
			}
			t /= lengthSquared();
			t = CLAMP(t, 0, 1);
			return lerp(t);
		}

		// Calculate the distance between the line and a given point
		T distance(const Point<T, dim>& point) const
		{
			return point.distance(closestPoint(point));
		}

		// Calculate the squared distance between the line and a given point
		T distanceSquared(const Point<T, dim>& point) const
		{
			return point.distanceSquared(closestPoint(point));
		}

		// Check if two lines are parallel
		bool isParallel(const Line<T, dim>& other) const
		{
			Vector<T, dim> dir1 = _end - _start;
			Vector<T, dim> dir2 = other._end - other._start;
			return dir1.cross(dir2).magnitude() < EPS;
		}

		// Check if two lines are perpendicular
		bool isPerpendicular(const Line<T, dim>& other) const
		{
			Vector<T, dim> dir1 = _end - _start;
			Vector<T, dim> dir2 = other._end - other._start;
			return dir1.dot(dir2) < EPS;
		}

		// Check if two lines are intersecting
		bool isIntersecting(const Line<T, dim>& other) const
		{
			Vector<T, dim> dir1 = _end - _start;
			Vector<T, dim> dir2 = other._end - other._start;
			Vector<T, dim> startDiff = _start - other._start;
			T a = dir1.cross(dir2).magnitude();
			T b = dir1.cross(startDiff).magnitude();
			T c = dir2.cross(startDiff).magnitude();
			return a < EPS && b < EPS && c < EPS;
		}

		// Check if two lines are intersecting and get the intersection point
		bool isIntersecting(const Line<T, dim>& other, Point<T, dim>& intersection) const
		{
			Vector<T, dim> dir1 = _end - _start;
			Vector<T, dim> dir2 = other._end - other._start;
			Vector<T, dim> startDiff = _start - other._start;
			T a = dir1.cross(dir2).magnitude();
			T b = dir1.cross(startDiff).magnitude();
			T c = dir2.cross(startDiff).magnitude();
			if (a < EPS && b < EPS && c < EPS)
			{
				T t = b / a;
				intersection = _start.lerp(_end, t);
				return true;
			}
			return false;
		}

		// Check if two lines are intersecting and get the intersection parameter
		bool isIntersecting(const Line<T, dim>& other, T& t) const
		{
			Vector<T, dim> dir1 = _end - _start;
			Vector<T, dim> dir2 = other._end - other._start;
			Vector<T, dim> startDiff = _start - other._start;
			T a = dir1.cross(dir2).magnitude();
			T b = dir1.cross(startDiff).magnitude();
			T c = dir2.cross(startDiff).magnitude();
			if (a < EPS && b < EPS && c < EPS)
			{
				t = b / a;
				return true;
			}
			return false;
		}

		// Check if two lines are intersecting and get the intersection point and parameter
		bool isIntersecting(const Line<T, dim>& other, Point<T, dim>& intersection, T& t) const
		{
			Vector<T, dim> dir1 = _end - _start;
			Vector<T, dim> dir2 = other._end - other._start;
			Vector<T, dim> startDiff = _start - other._start;
			T a = dir1.cross(dir2).magnitude();
			T b = dir1.cross(startDiff).magnitude();
			T c = dir2.cross(startDiff).magnitude();
			if (a < EPS && b < EPS && c < EPS)
			{
				t = b / a;
				intersection = _start.lerp(_end, t);
				return true;
			}
			return false;
		}

		// Get the direction vector of the line
		Vector<T, dim> direction() const
		{
			return _end - _start;
		}

		// Extend the line by a distance
		Line<T, dim> extend(T distance) const
		{
			Vector<T, dim> dir = direction();
			dir.normalize();
			dir *= distance;
			return Line<T, dim>(_start - dir, _end + dir);
		}

		// Extend the line by a distance from the start
		Line<T, dim> extendStart(T distance) const
		{
			Vector<T, dim> dir = direction();
			dir.normalize();
			dir *= distance;
			return Line<T, dim>(_start - dir, _end);
		}

		// Extend the line by a distance from the end
		Line<T, dim> extendEnd(T distance) const
		{
			Vector<T, dim> dir = direction();
			dir.normalize();
			dir *= distance;
			return Line<T, dim>(_start, _end + dir);
		}

		// Check if two lines are equal
		bool operator==(const Line<T, dim>& other) const
		{
			return _start == other._start && _end == other._end;
		}

		// Check if two lines are not equal
		bool operator!=(const Line<T, dim>& other) const
		{
			return _start != other._start || _end != other._end;
		}
	};
}