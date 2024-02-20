#pragma once

namespace Tosh
{
#define EPS 1e-6
#define PI 3.14159265358979323846

#define DEG2RAD(x) ((x) * PI / 180.0)
#define RAD2DEG(x) ((x) * 180.0 / PI)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define CLAMP(x, a, b) (MIN(MAX((x), (a)), (b)))

#define LERP(a, b, t) ((a) + (t) * ((b) - (a)))

#define ABS(x) ((x) < 0 ? -(x) : (x))

#define SQR(x) ((x) * (x))

#define SIGN(x) ((x) < 0 ? -1 : 1)

#define EQUAL(a, b) (ABS((a) - (b)) < EPS)
#define NOT_EQUAL(a, b) (ABS((a) - (b)) > EPS)
}