#include "Object.h"


std::string const Object::tab = "    ";

vec3f Object::getPosition() {
    return position;
}

vec3f Object::getRotation() {
    return rotation;
}

std::string Object::getName() {
    return "_" + name;
}

