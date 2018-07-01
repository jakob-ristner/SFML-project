#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Collider.h"

// Object representing hitboxes that the player will stop at, such as walls
class Obstacle {
public:
    Obstacle(sf::Vector2f pos, sf::Vector2f size);
    ~Obstacle();

    Collider getCollider();
    sf::Vector2f getPos();

private:
    sf::RectangleShape body;
    
};

class CellDoor {
public:
    CellDoor(sf::Vector2f pos, sf::Vector2f size, std::string link, sf::Vector2f linkPos);
    ~CellDoor();

    Collider getCollider();
    std::string getLinkedMap();
private:
    sf::RectangleShape body;
    sf::Vector2f linkPos;
    std::string link;
};
