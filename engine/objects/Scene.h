#pragma once
#include "Object.h"
#include <engine/graphics/Camera.h>


class Scene {
private:
    Camera camera;
    std::vector<Object> objects;

    std::string fileName = "";
    bool alreadyHasFileName = false;

public:
    Scene();
    explicit Scene(const std::string& _fileName);

    void update(OutputShader &shader);
    void save(const std::string& _fileName);
    bool loadFromFile(const std::string& _fileName);
    std::string makeMap();
};
