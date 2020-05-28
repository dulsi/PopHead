#include "pch.hpp"
#include "levers.hpp"
#include "ECS/Components/charactersComponents.hpp"
#include "ECS/Components/physicsComponents.hpp"
#include "ECS/Components/objectsComponents.hpp"
#include "ECS/Components/graphicsComponents.hpp"
#include "Utilities/joystickMacros.hpp"

namespace ph::system {

void Levers::update(float dt)
{
}

void Levers::onEvent(sf::Event e)
{
	if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::E)
		handleUsedLevers();
	else if(e.type == sf::Event::JoystickButtonPressed && e.joystickButton.button == PH_JOYSTICK_Y)
		handleUsedLevers();
}

void Levers::handleUsedLevers() const
{
	auto playerView = mRegistry.view<component::Player, component::BodyRect>();
	auto leverView = mRegistry.view<component::Lever, component::BodyRect, component::TextureRect>();

	for(auto player : playerView)
	{
		const auto& playerBody = playerView.get<component::BodyRect>(player);
		for(auto lever : leverView)
		{
			const auto& leverBody = leverView.get<component::BodyRect>(lever);
			auto& leverTextureRect = leverView.get<component::TextureRect>(lever);
			auto& leverDetails = leverView.get<component::Lever>(lever);

			if(leverDetails.turnOffAfterSwitch && leverDetails.isActivated)
				continue;

			if(intersect(leverBody, playerBody))
			{
				leverDetails.isActivated = !leverDetails.isActivated;
				leverTextureRect = leverDetails.isActivated ? IntRect(9, 0, 7, 15) : IntRect(0, 0, 7, 15);
				handleListeners(leverDetails.isActivated, leverDetails.id);
			}
		}
	}
}

void Levers::handleListeners(bool isActivated, u32 leverId) const
{
	auto listenersView = mRegistry.view<component::LeverListener>();
	for(auto leverListener : listenersView)
	{
		auto& listenerDetails = listenersView.get<component::LeverListener>(leverListener);
		if(listenerDetails.observedLeverId == leverId)
			listenerDetails.isActivated = true;
	}
}

}

