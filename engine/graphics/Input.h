#pragma once
#include "../settings/PlayerControls.h"
#include "../patterns/Singleton.h"
#include "../math/vec2.h"


class Input: public Singleton<Input> {
public:
    PlayerControls &playerControls = PlayerControls::instance();
    vec2<float> deltaAngle= vec2<float>(0);
    vec2<float> moveDirection = vec2<float>(0);

    void update(sf::RenderWindow &window);
private:
    void keysUpdate();
    void mouseUpdate(sf::RenderWindow &window);
    static bool isOneKeyPressed(const sf::Keyboard::Key keys[]);
};

