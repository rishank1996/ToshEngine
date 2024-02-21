#include "vector.h"

using namespace Tosh;

Vec3f Tosh::vectorTrippleProduct(Vec3f a, Vec3f b, Vec3f c)
{
	return a.cross(b.cross(c));
}

Vec3d Tosh::vectorTrippleProduct(Vec3d a, Vec3d b, Vec3d c)
{
	return a.cross(b.cross(c));
}
