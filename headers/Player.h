#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
public:
    Player(sf::RectangleShape body);
    ~Player();
    sf::Vector2f getPos();
    void setPos(sf::Vector2f);
    void update(float dt);
    void draw(sf::RenderWindow &window);

private:
    sf::Vector2f pos;   
    sf::Vector2f vel;
    int speed;
    sf::RectangleShape body;

};