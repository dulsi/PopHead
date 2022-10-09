#pragma once

#include "Utilities/forceInline.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cmath>

namespace ph {

	constexpr float pi = 3.14159265359f;

	constexpr float nullFloat = -99999999.99f;
	const Vec2 nullVec2 = Vec2(nullFloat, nullFloat);

	template <typename T>
	FORCE_INLINE Vec2Base<T> hadamardMul(Vec2Base<T>, Vec2Base<T>);
	template <typename T>
	FORCE_INLINE Vec2Base<T> hadamardDiv(Vec2Base<T>, Vec2Base<T>);

	template <typename T>
	FORCE_INLINE Vec2Base<T> getUnitVector(Vec2Base<T>);

	FORCE_INLINE Vec2 getUnitVector(float angle);

	FORCE_INLINE float getMagnitude(Vec2); 
	
	FORCE_INLINE float degreesToRadians(float angle);
	FORCE_INLINE float radiansToDegrees(float angle);

	FORCE_INLINE Vec2u getTwoDimensionalPositionFromOneDimensionalArrayIndex(u32 index, u32 numberOfColumns);

	FORCE_INLINE bool isPointInsideCircle(Vec2 point, Vec2 circlePos, float radius);

	FORCE_INLINE bool intersect(FloatRect rect, Vec2 circlePos, float radius);

	FORCE_INLINE Vec2 lerp(Vec2 source, Vec2 destination, float speed);
	FORCE_INLINE float lerp(float source, float destination, float speed);

	template <typename T>
	FORCE_INLINE float distanceBetweenPoints(Vec2Base<T> point1, Vec2Base<T> point2);

	template <typename T>
	FORCE_INLINE Vec2Base<T> absVec(Vec2Base<T>);

	FORCE_INLINE Vec2 mod(Vec2, float);
	FORCE_INLINE Vec2 mod(Vec2, Vec2);

	FORCE_INLINE bool areApproximatelyEqual(float a, float b, float maxApproximation);
	FORCE_INLINE bool areApproximatelyEqual(Vec2 a, Vec2 b, float maxApproximation);
}

namespace ph {

	template<typename T>
	Vec2Base<T> getUnitVector(Vec2Base<T> vec)
	{
		auto dist = distanceBetweenPoints(Vec2(), vec);
		return vec / dist;
	}

	template <typename T>
	Vec2Base<T> hadamardMul(Vec2Base<T> a, Vec2Base<T> b)
	{
		Vec2Base<T> res;
		res.x = a.x * b.x;
		res.y = a.y * b.y;
		return res;
	}

	template <typename T>
	Vec2Base<T> hadamardDiv(Vec2Base<T> a, Vec2Base<T> b)
	{
		Vec2Base<T> res;
		res.x = a.x / b.x;
		res.y = a.y / b.y;
		return res;
	}

	template <typename T>
	float distanceBetweenPoints(Vec2Base<T> point1, Vec2Base<T> point2)
	{
		auto diff1 = point1.x - point2.x;
		auto diff2 = point1.y - point2.y;
		diff1 *= diff1;
		diff2 *= diff2;
		return Cast<float>(std::sqrt(diff1 + diff2));
	}

	template<typename T>
	Vec2Base<T> absVec(Vec2Base<T> vec)
	{
		return Vec2Base<T>(std::abs(vec.x), std::abs(vec.y));
	}
}
//#include "math.inl"
