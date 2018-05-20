#pragma region include
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
#include "./headers/DevConsole.h"
#pragma endregion
int main() {
    const sf::Color bgColor(51, 51, 51);
    sf::Font font;
    sf::Vector2i mousePos;
    sf::Vector2i mousePosRelative;
    font.loadFromFile("font.ttf");
    sf::Text text;
    text.setString("W: Forward\nA: Left\nS: Down\nD: Right\nQ: Rotate left\nE: Rotate right");
    text.setFont(font);
    text.setPosition(sf::Vector2f(20, 20));
    text.setFillColor(sf::Color::White);

    // Initialization of important stuff
    Settings settings = Settings();

    sf::RenderWindow window(sf::VideoMode(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT), "SFML Dungeon Crawler", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(120);

    sf::View viewport(sf::Vector2f((float) settings.WINDOW_WIDTH / 2.0f, (float) settings.WINDOW_HEIGHT / 2.0f), sf::Vector2f(settings.WINDOW_WIDTH, settings.WINDOW_HEIGHT));
    window.setView(viewport);
    window.setKeyRepeatEnabled(false);


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
    sf::Sprite foreGround;
    foreGround.setTexture(map.foreGroundTexture);
    foreGround.setPosition(sf::Vector2f(0.0f, 0.0f));

    bool isRunning = true;
    Player player = Player(sf::RectangleShape(sf::Vector2f(28.f, 28.f)));
    player.setPos(sf::Vector2f(settings.WINDOW_WIDTH / 2, settings.WINDOW_HEIGHT / 2 - 200));
    sf::Event event;
    Collider playerCol = player.getCollider();
    Fireball fireball = Fireball(player);
    MagicMissile magicMissile = MagicMissile(player);
    player.addSpell(&fireball);
    player.addSpell(&magicMissile);


    // Dev Console
    DevConsole console = DevConsole(settings);

    // Spell
    Spell *currspell;

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
            } else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case 54:
                        isRunning = console.open(window, player);
                        clock.restart();
                        break;
                    default:
                        break;
                }
            }
        }

        mousePos = sf::Mouse::getPosition(window);

        mousePos.y -= std::min(0, (int)(Settings::WINDOW_HEIGHT  / 2 - player.getPos().y));
        mousePos.x -= std::min(0, (int)(Settings::WINDOW_WIDTH / 2 - player.getPos().x));
        mousePos.y += std::min(0, (int)((map.getSize().y * Settings::TILESIZE - Settings::WINDOW_HEIGHT / 2) - player.getPos().y));
        mousePos.x += std::min(0, (int)((map.getSize().x * Settings::TILESIZE - Settings::WINDOW_WIDTH / 2) - player.getPos().x));
        player.setMousePos(sf::Vector2f(mousePos.x, mousePos.y));

        player.setRotation(360 - getAngle(player.getPos(),sf::Vector2f(mousePos.x, mousePos.y)));

        player.setMouseAngle(getAngle(player.getPos(),
                             sf::Vector2f(mousePos.x,
                             mousePos.y)));

        for (int i = 0; i < player.getProjectiles().size(); i++) {
            player.getProjectiles()[i].update(dt, sf::Vector2f(mousePos.x, mousePos.y));
        }
        player.update(dt);
        sf::Vector2f direction;

        // Collision detection
        if (settings.playerColliding) {
            for (Obstacle &obstacle : obstacles) {
                if (obstacle.getCollider().checkCollision(playerCol, direction, 1.0f)) {
                    player.onCollision(direction);
                }
            }
        }
        viewport.setCenter(clampVec(player.getPos(), lowerBound, upperBound));
        window.setView(viewport);


        // Drawing
        window.clear(bgColor);


        window.draw(someSprite);

        for (int i = 0; i < player.getProjectiles().size(); i++) {
            player.getProjectiles()[i].draw(window);
        }
        player.draw(window);
        window.draw(foreGround);
        window.draw(text);

        window.display();
    }

    return 0;
}
