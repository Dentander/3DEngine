#pragma once
#include <SFML/Graphics.hpp>
#include "../math/vec3.h"
#include "../math/vec2.h"
#include "Input.h"
#include "Camera.h"

class Engine {
private:
    sf::RenderTexture outputTexture;
    sf::Sprite outputTextureSprite;
    sf::Shader outputShader;

    Camera camera;

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

    void setUniform(const std::string& name, vec2f vec);
    void setUniform(const std::string& name, vec3f vec);
    void setUniform(const std::string& name, float num);
    void setUniform(const std::string& name, int num);

    int getWidth() const;
    int getHeight() const;
    vec2f getSize() const;
};

