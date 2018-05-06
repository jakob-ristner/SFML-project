
#include <SFML/Graphics.hpp>
#include <iostream>
#include "./settings.cpp"
#include "headers/Player.h"


int main() {
    // Initialization of important stuff
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Dungeon Crawler", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    sf::View viewport(sf::Vector2f((float) WINDOW_WIDTH / 2.0f, (float) WINDOW_HEIGHT / 2.0f), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    window.setView(viewport);

    sf::Clock clock;

    bool isRunning = true;
    Player player = Player(sf::RectangleShape(sf::Vector2f(32.f, 32.f)));
    player.setPos(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
    sf::Event event;

    // Main Game Loop
    clock.restart();
    float dt = 0;
    while (isRunning) {
        dt = clock.restart().asMilliseconds();
        
        // Event Loop
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isRunning = false;
                window.close();
            }
        }
        player.update(dt);

        // Drawing
        window.clear(bgColor);
        player.draw(window);
        window.display();
    }

    return 0;
}
