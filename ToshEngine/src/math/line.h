#pragma once

#include "core.h"
#include "vector.h"
#include "point.h"

namespace Tosh
{
	// templated class representing a parametric line taking a point and a vector direction
	template <class T, size_t dim>
	class Line
	{
	private:
		// the point on the line
		Point<T,dim> m_point;

		// the direction of the line
		Vector<T,dim> m_direction;
	public:
		// default constructor
		Line() : m_point(), m_direction() {}

		// constructor taking two points
		Line(const Point<T,dim>& p1, const Point<T,dim>& p2) : m_point(p1), m_direction(p2 - p1) {}

		// constructor taking a point and a vector
		Line(const Point<T,dim>& point, const Vector<T,dim>& direction) : m_point(point), m_direction(direction) {}

		// copy constructor
		Line(const Line<T, dim>& line) : m_point(line.m_point), m_direction(line.m_direction) {}

		// move constructor
		Line(Line<T, dim>&& line) : m_point(std::move(line.m_point)), m_direction(std::move(line.m_direction)) {}

		// destructor
		~Line() {}

		// assignment operator
		Line<T, dim>& operator=(const Line<T, dim>& line)
		{
			m_point = line.m_point;
			m_direction = line.m_direction;
			return *this;
		}

		// move assignment operator
		Line<T, dim>& operator=(Line<T, dim>&& line)
		{
			m_point = std::move(line.m_point);
			m_direction = std::move(line.m_direction);
			return *this;
		}

		// get the point
		const Point<T, dim>& getPoint() const { return m_point; }

		// get the direction
		const Vector<T, dim>& getDirection() const { return m_direction; }

		// get a point on the line at a given parameter
		Point<T, dim> pointAt(T t) const
		{
			return m_point + m_direction * t;
		}

		// get the closest point on the line to a given point
		Point<T, dim> closestPoint(const Point<T, dim>& point) const
		{
			Vector<T, dim> v = point - m_point;
			T t = v.dot(m_direction) / m_direction.lengthSquared();
			return pointAt(t);
		}

		// get the distance from the line to a given point
		T distance(const Point<T, dim>& point) const
		{
			return (point - closestPoint(point).distance();
		}

		// get the distance from the line to another line
		T distance(const Line<T, dim>& line) const
		{
			Vector<T, dim> v = m_point - line.m_point;
			Vector<T, dim> n = cross(m_direction, line.m_direction);
			return fabs(v.dot(n) / n.length());
		}

		// are two lines parallel
		bool isParallel(const Line<T, dim>& line) const
		{
			return m_direction.isParallel(line.m_direction);
		}

		// are two lines perpendicular
		bool isPerpendicular(const Line<T, dim>& line) const
		{
			return m_direction.isPerpendicular(line.m_direction);
		}
	};
}