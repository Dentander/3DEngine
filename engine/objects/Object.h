#pragma once
#include <engine/math/vec3.h>
#include <engine/graphics/OutputShader.h>


class Object {
protected:
    std::string name;
    vec3f position = vec3f(0);
    vec3f rotation = vec3f(0);
    vec3f color = vec3f(0.5);
    int material = 0;

public:
    static const std::string tab;

    Object() {  }
    Object(vec3f _position, vec3f _rotation) : position(_position), rotation(_rotation) {  }

    virtual void input() = 0;
    virtual void update() = 0;
    virtual std::string toMap() = 0;

    std::string getName();
    vec3f getPosition();
    vec3f getRotation();
};
