#include "../settings/PlayerControls.h"
#include "Input.h"


bool Input::isOneKeyPressed(const sf::Keyboard::Key keys[2]) {
    for (int i = 0; i < 2; i++)
        if (sf::Keyboard::isKeyPressed(keys[i]))
            return true;
    return false;
}

void Input::keysUpdate() {
    moveDirection = vec2<float>(0);
    if (isOneKeyPressed(playerControls.forward)) {
        moveDirection = moveDirection + vec2<float>(1, 0);
    }
    if (isOneKeyPressed(playerControls.backward)){
        moveDirection = moveDirection + vec2<float>(-1, 0);
    }
    if (isOneKeyPressed(playerControls.right)){
        moveDirection = moveDirection + vec2<float>(0, 1);
    }
    if (isOneKeyPressed(playerControls.left)){
        moveDirection = moveDirection + vec2<float>(0, -1);
    }
}

void Input::mouseUpdate(sf::RenderWindow &window) {
    static bool wasFocused = false;
    float halfWidth = (float)window.getSize().x / 2;
    float halfHeight = (float)window.getSize().y / 2;
    if (true) {
        window.setMouseCursorVisible(false);
        if (window.hasFocus()){
            if (not wasFocused) { sf::Mouse::setPosition(sf::Vector2i(halfWidth, halfHeight), window); }
            else {
                sf::Vector2i deltaPosition = sf::Mouse::getPosition(window) - sf::Vector2i(halfWidth, halfHeight);
                deltaAngle.x = deltaPosition.x, deltaAngle.y = deltaPosition.y;
                sf::Mouse::setPosition(sf::Vector2i(halfWidth, halfHeight), window);
            }
        }
    }
    else if (true) {
        window.setMouseCursorVisible(true);
    }
    wasFocused = window.hasFocus();
}

void Input::update(sf::RenderWindow &window) {
    keysUpdate();
    mouseUpdate(window);
}

