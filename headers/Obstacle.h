#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Obstacle{
public:
    Obstacle(sf::Vector2f pos, sf::Vector2f size);
    ~Obstacle();

    Collider getCollider();

private:
    sf::RectangleShape body;
    
};