#include "Engine.h"


Engine::Engine() {
    // ======== WINDOW ========
    window.create(sf::VideoMode(getWidth(), getHeight()), "3DEngine");
    window.setVerticalSyncEnabled(true);
    shader.build(getSize());
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

    // ======== SCENE ========
    scene.update(shader);
}

void Engine::draw() {
    // ======== SHADER ========
    shader.draw(window);
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
