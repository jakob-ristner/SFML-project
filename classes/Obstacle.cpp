#include <SFML/Graphics.hpp>
#include "../headers/Obstacle.h"


Obstacle::Obstacle(sf::Vector2f pos, sf::Vector2f size) {
    body = sf::RectangleShape(size);
    body.setPosition(pos);
}

Obstacle::~Obstacle() {

}

Collider Obstacle::getCollider() {
    return Collider(body, sf::Vector2f(0.0f, 0.0f));
}