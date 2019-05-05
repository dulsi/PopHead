#ifndef POPHEAD_INPUT_KEYBOARDMANAGER_H_
#define POPHEAD_INPUT_KEYBOARDMANAGER_H_

#include <SFML/Window.hpp>
#include <map>

namespace PopHead {
namespace Input {


struct KeyboardManager
{
    bool isKeyPressed( sf::Keyboard::Key ) const;
    bool isKeyJustPressed( sf::Keyboard::Key ) const;
    bool isKeyJustReleased( sf::Keyboard::Key ) const;
};


}}

#endif // !POPHEAD_INPUT_KEYBOARDMANAGER_H_
