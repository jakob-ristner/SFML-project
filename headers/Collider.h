#pragma once
#include <SFML/Graphics.hpp>

class Collider {
public:
    Collider(sf::RectangleShape body, sf::Vector2f velocity);
    ~Collider();

    // Maybe not needed
    void move(float dx, float dy);

    bool checkCollision(Collider& other, sf::Vector2f& direction, float push);
    sf::Vector2f getPosition();
    sf::Vector2f getHalfSize();

private:
    sf::RectangleShape body;
    sf::Vector2f velocity;
};
