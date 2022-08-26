#include <engine/graphics/ParameterSystem.h>
#include "engine/graphics/Engine.h"


int main() {
    Engine engine;
    engine.run();
    return EXIT_SUCCESS;
}


/*int main() {
    ParameterSystem params;
    params.insert("a", 12);
    params.insert("b", 13);
    params.insert("c", vec3f(0));
    params.insert("ds", vec2f(0));
}*/


/*#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <thread>
#include <fstream>
#include <conio.h>
#include <SFML/OpenGL.hpp>



using namespace std;


class A {
protected:
    int a;
    A(int a) : a(a) {};
public:
    A() = default;
    virtual void Show() {}
};

class B : public A {
public:
    B() : A(1) {};
    void Show() override { cout << "b\n"; }
};

class C : public A {
public:
    C() : A(2) {};
    void Show() override { cout << "c\n"; }
};





int main() {
    vector<A*> mass;
    B* b = new B();
    C* c = new C();
    mass.push_back(b);
    mass.push_back(c);

    for (auto item : mass) {
        item->Show();
    }

    return 0;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    window.setFramerateLimit(60);

    sf::RenderTexture firstTexture;
    firstTexture.create(800, 600);
    sf::Sprite firstTextureSprite = sf::Sprite(firstTexture.getTexture());
    sf::Sprite firstTextureSpriteFlipped = sf::Sprite(firstTexture.getTexture());
    firstTextureSpriteFlipped.setScale(1, -1);
    firstTextureSpriteFlipped.setPosition(0, 600);

    sf::RenderTexture outputTexture;
    outputTexture.create(800, 600);
    sf::Sprite outputTextureSprite = sf::Sprite(outputTexture.getTexture());
    sf::Sprite outputTextureSpriteFlipped = sf::Sprite(firstTexture.getTexture());
    outputTextureSpriteFlipped.setScale(1, -1);
    outputTextureSpriteFlipped.setPosition(0, 600);

    sf::Shader shader;
    shader.loadFromFile("PixelShader.glsl", sf::Shader::Fragment);
    shader.setUniform("u_resolution", sf::Vector2f(800, 600));

    // ofstream myfile;
    //myfile.open("PixelShader.glsl");
    //myfile << "#version 330 core\nlayout (location = 0) out vec4 fragColor;\n\nvoid main() {\nfragColor = vec4(1, 0, 0, 1);\n}";
    // myfile.close();





    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        outputTexture.draw(firstTextureSpriteFlipped, &shader);
        window.draw(outputTextureSprite);

        if (_kbhit()) {
            try
            {
                string a;
                cin >> a;
                cout << stoi(a) + 1 << "\n";
                cin.ignore();
            }
            catch (const std::exception&)
            {
                cout << "false\n";
            }


        }
        window.display();
    }

    return 0;
}*/