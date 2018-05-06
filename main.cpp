#include <SFML/Graphics.hpp>
#include <iostream>
#include "./settings.cpp"

int main() {
    // Initialization of important stuff
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Dungeon Crawler", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    sf::View viewport(sf::Vector2f((float) WINDOW_WIDTH / 2.0f, (float) WINDOW_HEIGHT / 2.0f), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    window.setView(viewport);

    sf::Clock clock;

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
        window.display();
    }

    return 0;
}
