#pragma once

#include "core.h"
#include "vector.h"

using namespace Tosh;

namespace Tosh
{
	class Plane
	{
	private:
		Vec3f _normal;
		float _d;

	public:
		Plane(const Vec3f& normal, float d) : _normal(normal), _d(d) {}

		Plane(const Vec3f& normal, const Vec3f& point) : _normal(normal), _d(normal.dot(point)) {}

		Plane(const Vec3f& p1, const Vec3f& p2, const Vec3f& p3)
		{
			_normal = (p2 - p1).cross(p3 - p1).normalize();
			_d = _normal.dot(p1);
		}

		// copy constructor
		Plane(const Plane& plane) : _normal(plane._normal), _d(plane._d) {}

		// move constructor
		Plane(Plane&& plane) : _normal(std::move(plane._normal)), _d(std::move(plane._d)) {}

		// copy assignment
		Plane& operator=(const Plane& plane)
		{
			_normal = plane._normal;
			_d = plane._d;
			return *this;
		}

		// move assignment
		Plane& operator=(Plane&& plane)
		{
			_normal = std::move(plane._normal);
			_d = std::move(plane._d);
			return *this;
		}

		// destructor
		~Plane() {}

		inline const Vec3f& normal() const { return _normal; }
		inline float d() const { return _d; }

		inline float distance(const Vec3f& point) const { return _normal.dot(point) - _d; }

		inline Vec3f project(const Vec3f& point) const { return point - _normal * distance(point); }
	};
}
