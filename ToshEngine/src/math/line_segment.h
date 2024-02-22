#pragma once

#include "core.h"

namespace Tosh
{

	// Forward declarations
	class Point;
	class Vector;

	// Template class for representing a LineSegment in n-dimensional space
	template <class T, size_t dim = DIM3>
	class LineSegment
	{
	private:
		Point<T,dim> _start; // The starting point of the LineSegment
		Point<T, dim> _end; // The ending point of the LineSegment

	public:
		// Default constructor
		LineSegment() = default;

		// Constructor with start and end points
		LineSegment(const Point<T, dim>& start, const Point<T, dim>& end) : _start(start), _end(end) {}

		// Copy constructor
		LineSegment(const LineSegment<T, dim>& other) : _start(other._start), _end(other._end) {}

		// Move constructor
		LineSegment(LineSegment<T, dim>&& other) noexcept : _start(std::move(other._start)), _end(std::move(other._end)) {}

		// Destructor
		~LineSegment() = default;

		// Copy assignment operator
		LineSegment<T, dim>& operator=(const LineSegment<T, dim>& other)
		{
			_start = other._start;
			_end = other._end;
			return *this;
		}

		// Move assignment operator
		LineSegment<T, dim>& operator=(LineSegment<T, dim>&& other)
		{
			_start = std::move(other._start);
			_end = std::move(other._end);
			return *this;
		}

		// Get the starting point of the LineSegment
		Point<T, dim> start() const { return _start; }

		// Get the ending point of the LineSegment
		Point<T, dim> end() const { return _end; }

		// Calculate the length of the LineSegment
		T length() const
		{
			T result = 0;
			for (size_t i = 0; i < dim; i++)
			{
				result += SQR(_start[i] - _end[i]);
			}
			return sqrt(result);
		}

		// Calculate the squared length of the LineSegment
		T lengthSquared() const
		{
			T result = 0;
			for (size_t i = 0; i < dim; i++)
			{
				result += SQR(_start[i] - _end[i]);
			}
			return result;
		}

		// LineSegmentarly interpolate between the start and end points of the LineSegment
		Point<T, dim> lerp(T t) const
		{
			Point<T, dim> result;
			for (size_t i = 0; i < dim; i++)
			{
				result[i] = LERP(_start[i], _end[i], t);
			}
			return result;
		}

		// Get the closest point on the LineSegment to a given point
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

		// Calculate the distance between the LineSegment and a given point
		T distance(const Point<T, dim>& point) const
		{
			return point.distance(closestPoint(point));
		}

		// Calculate the squared distance between the LineSegment and a given point
		T distanceSquared(const Point<T, dim>& point) const
		{
			return point.distanceSquared(closestPoint(point));
		}

		// Check if two LineSegments are parallel
		bool isParallel(const LineSegment<T, dim>& other) const
		{
			Vector<T, dim> dir1 = _end - _start;
			Vector<T, dim> dir2 = other._end - other._start;
			return dir1.cross(dir2).magnitude() < EPS;
		}

		// Check if two LineSegments are perpendicular
		bool isPerpendicular(const LineSegment<T, dim>& other) const
		{
			Vector<T, dim> dir1 = _end - _start;
			Vector<T, dim> dir2 = other._end - other._start;
			return dir1.dot(dir2) < EPS;
		}

		// Check if two LineSegments are intersecting
		bool isIntersecting(const LineSegment<T, dim>& other) const
		{
			Vector<T, dim> dir1 = _end - _start;
			Vector<T, dim> dir2 = other._end - other._start;
			Vector<T, dim> startDiff = _start - other._start;
			T a = dir1.cross(dir2).magnitude();
			T b = dir1.cross(startDiff).magnitude();
			T c = dir2.cross(startDiff).magnitude();
			return a < EPS && b < EPS && c < EPS;
		}

		// Check if two LineSegments are intersecting and get the intersection point
		bool isIntersecting(const LineSegment<T, dim>& other, Point<T, dim>& intersection) const
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

		// Check if two LineSegments are intersecting and get the intersection parameter
		bool isIntersecting(const LineSegment<T, dim>& other, T& t) const
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

		// Check if two LineSegments are intersecting and get the intersection point and parameter
		bool isIntersecting(const LineSegment<T, dim>& other, Point<T, dim>& intersection, T& t) const
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

		// Get the direction vector of the LineSegment
		Vector<T, dim> direction() const
		{
			return _end - _start;
		}

		// Extend the LineSegment by a distance
		LineSegment<T, dim> extend(T distance) const
		{
			Vector<T, dim> dir = direction();
			dir.normalize();
			dir *= distance;
			return LineSegment<T, dim>(_start - dir, _end + dir);
		}

		// Extend the LineSegment by a distance from the start
		LineSegment<T, dim> extendStart(T distance) const
		{
			Vector<T, dim> dir = direction();
			dir.normalize();
			dir *= distance;
			return LineSegment<T, dim>(_start - dir, _end);
		}

		// Extend the LineSegment by a distance from the end
		LineSegment<T, dim> extendEnd(T distance) const
		{
			Vector<T, dim> dir = direction();
			dir.normalize();
			dir *= distance;
			return LineSegment<T, dim>(_start, _end + dir);
		}

		// Check if two LineSegments are equal
		bool operator==(const LineSegment<T, dim>& other) const
		{
			return _start == other._start && _end == other._end;
		}

		// Check if two LineSegments are not equal
		bool operator!=(const LineSegment<T, dim>& other) const
		{
			return _start != other._start || _end != other._end;
		}
	};

	// usefull typedefs
	typedef LineSegment<float, DIM2> LineSegment2f;
	typedef LineSegment<float, DIM3> LineSegment3f;
	typedef LineSegment<double, DIM2> LineSegment2d;
	typedef LineSegment<double, DIM3> LineSegment3d;
}