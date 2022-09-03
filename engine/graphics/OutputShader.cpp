#include "OutputShader.h"


OutputShader::OutputShader(vec2f size) {
    build(size);
}

void OutputShader::build(vec2f size) {
    outputShader.loadFromFile("glsl/Fragment.glsl", sf::Shader::Fragment);
    outputTexture.create(size.x, size.y);
    outputTextureSprite = sf::Sprite(outputTexture.getTexture());
    setUniform("u_resolution", size);
}

void OutputShader::draw(sf::RenderWindow &window) {
    outputTexture.create(window.getSize().x, window.getSize().y);
    outputTextureSprite = sf::Sprite(outputTexture.getTexture());
    outputTexture.draw(outputTextureSprite, &outputShader);

    //outputTextureSprite.setPosition(0, 0);
    window.draw(outputTextureSprite);
}

void OutputShader::setUniform(const std::string& name, float uniform) {
    outputShader.setUniform(name, uniform);
}

void OutputShader::setUniform(const std::string& name, int uniform) {
    outputShader.setUniform(name, uniform);
}

void OutputShader::setUniform(const std::string& name, vec2f uniform) {
    outputShader.setUniform(name, uniform.toSFML());
}

void OutputShader::setUniform(const std::string& name, vec3f uniform) {
    outputShader.setUniform(name, uniform.toSFML());
}


