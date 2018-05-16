#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

// Object representing hitboxes that the player will stop at, such as walls
class Obstacle{
public:
    Obstacle(sf::Vector2f pos, sf::Vector2f size);
    ~Obstacle();

    Collider getCollider();
    sf::Vector2f getPos();

private:
    sf::RectangleShape body;
    
};
