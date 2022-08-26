#pragma once
#include <engine/math/vec3.h>
#include "Input.h"
#include "Transform.h"
#include "ParameterSystem.h"
#include <variant>


class Camera {
private:
    ParameterSystem& params = ParameterSystem::instance();
    Input &input = Input::instance();
    PlayerControls &playerControls = PlayerControls::instance();

    vec3f position = vec3f(0, 0, -3);
    vec2f rotation = vec2f(0);

    void updateRotation();
    void updatePosition();

public:
    Camera();
    explicit Camera(vec3f position, vec2f rotation);

    void update();

    void setUniforms(sf::Shader &shader);
    void setPosition(vec3f position);
    void setRotation(vec2f rotation);
    void addPosition(vec3f position);
    void addRotation(vec2f rotation);
    vec3f getPosition();
    vec2f getRotation();
};
