#pragma once

#include <gtest/gtest.h>
#include "math/vector.h"

using namespace Tosh;

// GTests
TEST(Vector, Magnitude) {
	Vec2f v1(3.0f, 4.0f);
	EXPECT_FLOAT_EQ(v1.magnitude(), 5.0f);

	Vec3f v2(1.0f, 2.0f, 3.0f);
	EXPECT_FLOAT_EQ(v2.magnitude(), sqrt(14.0f));
}

TEST(Vector, DotProduct) {
	Vec2f v1(1.0f, 2.0f);
	Vec2f v2(3.0f, 4.0f);
	EXPECT_FLOAT_EQ(v1.dot(v2), 11.0f);

	Vec3f v3(1.0f, 2.0f, 3.0f);
	Vec3f v4(4.0f, 5.0f, 6.0f);
	EXPECT_FLOAT_EQ(v3.dot(v4), 32.0f);
}

TEST(Vector, CrossProduct) {
	Vec3f v1(1.0f, 2.0f, 3.0f);
	Vec3f v2(4.0f, 5.0f, 6.0f);
	Vec3f result = v1.cross(v2);
	Vec3f expected(-3.0f, 6.0f, -3.0f);
	EXPECT_EQ(result, expected);
}

TEST(Vector, Distance) {
	Vec2f v1(1.0f, 2.0f);
	Vec2f v2(4.0f, 6.0f);
	EXPECT_FLOAT_EQ(v1.distance(v2), 5.0f);

	Vec3f v3(1.0f, 2.0f, 3.0f);
	Vec3f v4(4.0f, 6.0f, 8.0f);
	EXPECT_FLOAT_EQ(v3.distance(v4), sqrt(50.0f));
}

TEST(Vector, Angle) {
	Vec2f v1(1.0f, 0.0f);
	Vec2f v2(0.0f, 1.0f);
	EXPECT_FLOAT_EQ(v1.angle(v2), PI / 2.0f);

	Vec3f v3(1.0f, 0.0f, 0.0f);
	Vec3f v4(0.0f, 1.0f, 0.0f);
	EXPECT_FLOAT_EQ(v3.angle(v4), PI / 2.0f);
}

TEST(Vector, Projection) {
	Vec2f v1(3.0f, 4.0f);
	Vec2f v2(1.0f, 1.0f);
	Vec2f result = v1.project(v2);
	Vec2f expected(3.5f, 3.5f);
	EXPECT_EQ(result, expected);

	Vec3f v3(1.0f, 2.0f, 3.0f);
	Vec3f v4(1.0f, 0.0f, 0.0f);
	Vec3f result2 = v3.project(v4);
	Vec3f expected2(1.0f, 0.0f, 0.0f);
	EXPECT_EQ(result2, expected2);
}

TEST(Vector, Rejection) {
	Vec2f v1(3.0f, 4.0f);
	Vec2f v2(1.0f, 1.0f);
	Vec2f result = v1.reject(v2);
	Vec2f expected(-0.5f, 0.5f);
	EXPECT_EQ(result, expected);

	Vec3f v3(1.0f, 2.0f, 3.0f);
	Vec3f v4(1.0f, 0.0f, 0.0f);
	Vec3f result2 = v3.reject(v4);
	Vec3f expected2(0.0f, 2.0f, 3.0f);
	EXPECT_EQ(result2, expected2);
}
