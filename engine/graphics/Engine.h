#pragma once
#include "Input.h"
#include "Camera.h"
#include "OutputShader.h"
#include <SFML/Graphics.hpp>
#include <engine/objects/Scene.h>
#include <engine/math/vec3.h>


class Engine {
private:
    OutputShader shader;

    Scene scene;

    Input &input = Input::instance();

    void eventsUpdate();
    void update();
    void draw();

protected:
    int width=1000, height=600;
    sf::RenderWindow window;

public:
    Engine();

    void run();
    void exit();

    int getWidth() const;
    int getHeight() const;
    vec2f getSize() const;
};

