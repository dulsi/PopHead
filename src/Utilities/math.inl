#include "math.hpp"
#include "Logs/logs.hpp"

namespace ph {

	Vec2 getUnitVector(float angle)
	{
		auto radians = degreesToRadians(angle);
		return Vec2(std::cosh(radians), std::sinh(radians));
	}

	float getMagnitude(Vec2 v)
	{
		return std::hypotf(v.x, v.y);	
	}

	float degreesToRadians(float angle)
	{
		return angle * pi / 180.f;
	}

	float radiansToDegrees(float angle)
	{
		return angle * 180.f / pi;
	}

	Vec2u getTwoDimensionalPositionFromOneDimensionalArrayIndex(u32 index, u32 numberOfColumns)
	{
		PH_ASSERT_UNEXPECTED_SITUATION(numberOfColumns != 0, "Number of columns cannot be 0");
		return Vec2u(index % numberOfColumns, index / numberOfColumns);
	}

	bool isPointInsideCircle(Vec2 point, Vec2 circlePos, float radius)
	{
		return distanceBetweenPoints(point, circlePos) < radius;
	}

	bool intersect(FloatRect rect, Vec2 circlePos, float radius)
	{
		return rect.contains(circlePos) || 
		       isPointInsideCircle(rect.pos, circlePos, radius) ||
		       isPointInsideCircle(rect.topRight(), circlePos, radius) ||
		       isPointInsideCircle(rect.bottomLeft(), circlePos, radius) ||
		       isPointInsideCircle(rect.bottomRight(), circlePos, radius) ||
		       isPointInsideCircle(rect.topCenter(), circlePos, radius) ||
		       isPointInsideCircle(rect.bottomCenter(), circlePos, radius) ||
		       isPointInsideCircle(rect.leftCenter(), circlePos, radius) ||
		       isPointInsideCircle(rect.rightCenter(), circlePos, radius); 
	}

	Vec2 lerp(Vec2 source, Vec2 destination, float speed)
	{
		PH_ASSERT_UNEXPECTED_SITUATION(speed >= 0.f, "Speed cannot be less than 0");
		return source + (destination - source) * speed;
	}

	float lerp(float source, float destination, float speed)
	{
		PH_ASSERT_UNEXPECTED_SITUATION(speed >= 0.f, "Speed cannot be less than 0");
		return source + (destination - source) * speed;
	}

	bool areApproximatelyEqual(float a, float b, float maxApproximation)
	{
		PH_ASSERT_UNEXPECTED_SITUATION(maxApproximation >= 0.f, "max approximation has to be positive value");
		return (std::fabs(a - b) < maxApproximation);
	}

	bool areApproximatelyEqual(Vec2 a, Vec2 b, float maxApproximation)
	{
		return areApproximatelyEqual(a.x, b.x, maxApproximation) && areApproximatelyEqual(a.y, b.y, maxApproximation);
	}

	Vec2 mod(Vec2 a, float b)
	{
		return Vec2(fmod(a.x, b), fmod(a.y, b));
	}

	Vec2 mod(Vec2 a, Vec2 b)
	{
		return Vec2(fmod(a.x, b.x), fmod(a.y, b.y));
	}
}
