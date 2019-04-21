#ifndef POPHEAD_UTILITIES_MATH_H_
#define POPHEAD_UTILITIES_MATH_H_

#include <SFML/Graphics.hpp>
#include <cassert>

namespace PopHead {
namespace Utilities {

namespace Math {
	inline auto getRightBound(sf::FloatRect bounds) -> float { return bounds.left + bounds.width; }

	inline auto getBottomBound(sf::FloatRect bounds) -> float { return bounds.top + bounds.height; }

	inline auto getCenter(sf::FloatRect bounds) -> sf::Vector2f{ return sf::Vector2f(getRightBound(bounds) / 2.f, getBottomBound(bounds) / 2.f); }

	inline auto lerp(sf::Vector2f source, sf::Vector2f destination, float speed) -> sf::Vector2f
	{
		assert(speed >= 0.f, "speed can't be less than 0");
		return source + (destination - source) * speed;
	}
}

}
}

#endif
