
#include <SFML/Graphics.hpp>
#include <iostream>
#include "headers/Player.h"
#include "headers/Settings.h"


int main() {

    const sf::Color bgColor(51, 51, 51);         

    // Initialization of important stuff
    Settings settings = Settings();

    sf::RenderWindow window(sf::VideoMode(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT), "SFML Dungeon Crawler", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    sf::View viewport(sf::Vector2f((float) settings.WINDOW_WIDTH / 2.0f, (float) settings.WINDOW_HEIGHT / 2.0f), sf::Vector2f(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT));
    window.setView(viewport);

    sf::Clock clock;

    bool isRunning = true;
    Player player = Player(sf::RectangleShape(sf::Vector2f(32.f, 32.f)));
    player.setPos(sf::Vector2f(settings.WINDOW_WIDTH / 2, settings.WINDOW_HEIGHT / 2));
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
