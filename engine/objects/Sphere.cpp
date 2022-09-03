#include "Sphere.h"

void Sphere::input() {
    std::string in;
}

std::string Sphere::toMap() {
    std::string sphereDist = name + "Dist",
                sphereMaterial = name + "Material";

    std::string result = tab + "// sphere \n";
    result +=            tab + "float " + sphereDist + " = fSphere(" + position.toMap() + ", " + std::to_string(radius) + "); \n";
    result +=            tab + "float " + sphereMaterial + " = " + std::to_string(material) + "; \n";
    return result;
}

Sphere::Sphere() {

}
