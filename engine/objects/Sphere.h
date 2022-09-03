#pragma once
#include "Object.h"


class Sphere: public Object {
protected:
    float radius = 1;

public:
    Sphere();

    void input() override;
    std::string toMap() override;
};
