#pragma once
#include <SFML/Graphics.hpp>
#include <engine/math/vec2.h>
#include <engine/math/vec3.h>


class OutputShader {
private:
    sf::RenderTexture outputTexture;
    sf::Sprite outputTextureSprite;
    sf::Shader outputShader;

public:
    OutputShader() = default;
    explicit OutputShader(vec2f size);

    void build(vec2f size);
    void draw(sf::RenderWindow &window);

    void setUniform(const std::string& name, float uniform);
    void setUniform(const std::string& name, int uniform);
    void setUniform(const std::string& name, vec2f uniform);
    void setUniform(const std::string& name, vec3f uniform);
};
