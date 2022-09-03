#include "Scene.h"

Scene::Scene() {

}

Scene::Scene(const std::string& _fileName) {
    loadFromFile(_fileName);
}

bool Scene::loadFromFile(const std::string& _fileName) {
    return false;
}

void Scene::save(const std::string& _fileName) {

}

void Scene::update(OutputShader &shader) {
    camera.update();
    camera.setUniforms(shader);
    for (auto &object : objects) {
        object.update();
    }
}

std::string Scene::makeMap() {
    std::string result = "vec4 map(vec3 p) { ";
    for (auto &object : objects) {
        result += object.toMap() + "\n";
    }
    return result + "}";
}

