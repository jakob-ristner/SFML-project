#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Settings.h"

class Player {
public:
    Player(sf::RectangleShape body);
    ~Player();
    sf::Vector2f getPos();
    void setPos(sf::Vector2f);
    void draw(sf::RenderWindow &window);
    void update(float dt);

private:
    sf::Vector2f pos;   
    sf::Vector2f vel;
    sf::Vector2f acc;
    sf::RectangleShape body;
    Settings settings;
    int speed;
    float playeracc = 2;
    float fric = 1.2;

};