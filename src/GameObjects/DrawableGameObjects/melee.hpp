#pragma once

#include "GameObjects/DrawableGameObject.hpp"
#include <array>

namespace ph{

class Swoosh {
public:
	Swoosh(const GameObject& opponentsNode, const sf::Vector2f direction, const unsigned damage, 
		const unsigned range);

private:
	const sf::Vector2f mDirection;
	const GameObject& mEnemiesNode;
	const float mDamage;
	const float mRange;
};


class MeleeWeapon : public DrawableGameObject
{
public:
	MeleeWeapon(GameData* const, const float damage, const float range);

	void update(const sf::Time delta) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void attack(const sf::Vector2f hitDirection);

private:
	void setMeleeWeaponPositionToRightHand(const sf::Vector2f attackDirection);
	void initializeAttackGraphics();
	void resetAttack();

private:
	std::array<sf::Vertex, 3> mAttackGraphic;
	sf::Clock mTimeFromLastHit;
	const float mDamage;
	const float mRange;
};

}