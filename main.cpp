
#include <SFML/Graphics.hpp>
#include <iostream>

#include "./headers/Settings.h"
#include "./headers/TileMap.h"
#include "./headers/Spell.h"
#include "./headers/Player.h"
#include "./headers/Settings.h"
#include "./headers/Utils.h"
#include "./headers/Collider.h"
#include "./headers/Obstacle.h"

int main() {

    const sf::Color bgColor(51, 51, 51);   
    sf::Font font;
    font.loadFromFile("font.ttf");  
    sf::Text text;
    text.setString("W: Forward\nA: Left\nS: Down\nD: Right\nQ: Rotate left\nE: Rotate right");
    text.setFont(font);
    text.setPosition(sf::Vector2f(20, 20));
    text.setColor(sf::Color::White);

    // Initialization of important stuff
    Settings settings = Settings();

    sf::RenderWindow window(sf::VideoMode(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT), "SFML Dungeon Crawler", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(120);

    sf::View viewport(sf::Vector2f((float) settings.WINDOW_WIDTH / 2.0f, (float) settings.WINDOW_HEIGHT / 2.0f), sf::Vector2f(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT));
    window.setView(viewport);

    // Vector with all obstacles - kind of like a sprite group
    std::vector<Obstacle> obstacles;

    sf::Clock clock;
    TileMap map = TileMap("./resources/map1", obstacles);
    sf::Sprite someSprite;
    someSprite.setTexture(map.mapTexture);
    someSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
    sf::Vector2f lowerBound(settings.WINDOW_WIDTH / 2.0f, settings.WINDOW_HEIGHT / 2.0f);
    sf::Vector2f upperBound(map.mapTexture.getSize().x - (settings.WINDOW_WIDTH / 2.0f), 
                            map.mapTexture.getSize().y - (settings.WINDOW_HEIGHT / 2.0f));

    bool isRunning = true;
    Player player = Player(sf::RectangleShape(sf::Vector2f(32.f, 32.f)));
    player.setPos(sf::Vector2f(settings.WINDOW_WIDTH / 2, settings.WINDOW_HEIGHT / 2 - 200));
    sf::Event event;
    Collider playerCol = player.getCollider();
    Spell:Spell spell = Fireball();   

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
        sf::Vector2f direction;

        // Collision detection
        for (Obstacle &obstacle : obstacles) {
            if (obstacle.getCollider().checkCollision(playerCol, direction, 1.0f)) {
                player.onCollision(direction);
                //std::cout << player.getPos().x << "," << player.getPos().y << std::endl;
            }
        }

        viewport.setCenter(clampVec(player.getPos(), lowerBound, upperBound));
        window.setView(viewport);

        
        // Drawing
        window.clear(bgColor);

        window.draw(someSprite);

        player.draw(window);
        window.draw(text);

        window.display();
    }

    return 0;
}
