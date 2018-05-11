#include <SFML/Graphics.hpp>
#include <iostream>
#include "./settings.cpp"
#include "./headers/TileMap.h"

int main() {
    // Initialization of important stuff
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Dungeon Crawler", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    sf::View viewport(sf::Vector2f((float) WINDOW_WIDTH / 2.0f, (float) WINDOW_HEIGHT / 2.0f), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    window.setView(viewport);

    sf::Clock clock;

    TileMap map = TileMap("./resources/testmap1.tmx");
    sf::Sprite someSprite;
    someSprite.setTexture(map.mapTexture);
    someSprite.setPosition(sf::Vector2f(0.0f, 0.0f));

    bool isRunning = true;
    sf::Event event;

    // Main Game Loop
    while (isRunning) {
        // Event Loop
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isRunning = false;
                window.close();
            }
        }

        window.clear(bgColor);
        window.draw(someSprite);
        window.display();
    }

    return 0;
}
