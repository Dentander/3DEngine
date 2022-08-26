#include "Engine.h"


Engine::Engine() {
    // ======== WINDOW ========
    window.create(sf::VideoMode(getWidth(), getHeight()), "3DEngine");
    window.setVerticalSyncEnabled(true);

    // ======== SHADER ========
    outputShader.loadFromFile("glsl/Fragment.glsl", sf::Shader::Fragment);
    outputTexture.create(getWidth(), getHeight());
    outputTextureSprite = sf::Sprite(outputTexture.getTexture());

    setUniform("u_resolution", getSize());

}

void Engine::eventsUpdate() {
    sf::Event event {};
    while (window.pollEvent(event)) {
        // ========= CLOSE ========
        if (event.type == sf::Event::Closed) { exit(); }

        // ========= KEYBOARD ========
        if (event.type == sf::Event::KeyPressed) {
            // ======== CLOSE ========
            if (event.key.code == sf::Keyboard::Escape) { exit(); }
        }

        // ======== RESIZE ========
        if (event.type == sf::Event::Resized) {
            width = window.getSize().x;
            height = window.getSize().y;
        }
    }
}

void Engine::update() {
    // ======== INPUT ========
    input.update(window);
    camera.update();
    camera.setUniforms(outputShader);

    // ======== SHADER ========
    outputTexture.create(getWidth(), getHeight());
    outputTextureSprite = sf::Sprite(outputTexture.getTexture());
    outputTexture.draw(outputTextureSprite, &outputShader);
}

void Engine::draw() {
    // ======== SHADER ========
    outputTextureSprite.setPosition(0, 0);
    window.draw(outputTextureSprite);
}

void Engine::run() {
    while (window.isOpen()) {
        // ======== EVENTS ========
        eventsUpdate();

        // ======== UPDATE ========
        update();

        // ======== DEBUG ========


        // ======== DRAW ========
        draw();

        // ======== DISPLAY AND DELAY ========
        window.display();
        window.clear();
    }
}

void Engine::exit() {
    window.close();
}

int Engine::getWidth() const { return width; }

int Engine::getHeight() const { return height; }

vec2f Engine::getSize() const { return vec2f((float)getWidth(), (float)getHeight()); }

void Engine::setUniform(const std::string& name, vec2<float> vec) {
    outputShader.setUniform(name, vec.toSFML());
}

void Engine::setUniform(const std::string& name, vec3<float> vec) {
    outputShader.setUniform(name, vec.toSFML());
}

void Engine::setUniform(const std::string &name, int num) {
    outputShader.setUniform(name, num);
}

void Engine::setUniform(const std::string &name, float num) {
    outputShader.setUniform(name, num);
}
