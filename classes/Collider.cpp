#include "../headers/Collider.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

Collider::Collider(sf::RectangleShape &body, sf::Vector2f velocity) :
    body(body){
    this->velocity = velocity;
}

Collider::~Collider() {

}

void Collider::move(float dx, float dy) {
    body.move(dx, dy);
}

bool Collider::checkCollision(Collider& other, sf::Vector2f& direction, float push) {
    sf::Vector2f otherPosition = other.getPosition();
    sf::Vector2f otherHalfSize = other.getHalfSize();
    sf::Vector2f thisPosition = getPosition();
    sf::Vector2f thisHalfSize = getHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = std::abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = std::abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f) {
        push = std::min(std::max(push, 0.0f), 1.0f);

        if (intersectX > intersectY) {
            if (deltaX > 0.0f) {
                move(intersectX * (1.0f - push), 0.0f);
                other.move(-intersectX  * push, 0.0f);

                direction.x = 1.0f;
                direction.y = 0.0f;
            } else {
                move(-intersectX * (1.0f - push), 0.0f);
                other.move(intersectX  * push, 0.0f);

                direction.x = -1.0f;
                direction.y = 0.0f;
            }
        } else {
            if (deltaY < 0.0f) {
                move(0.0f, -intersectY * (1.0f - push));
                other.move(0.0f, intersectY * push);

                direction.x = 0.0f;
                direction.y = 1.0f;
            } else {
                move(0.0f, intersectY * (1.0f - push));
                other.move(0.0f, -intersectY * push);

                direction.x = 0.0f;
                direction.y = -1.0f;
            }
        }
        return true;
    }
    return false;
}

sf::Vector2f Collider::getPosition() {
    return body.getPosition();
}

sf::Vector2f Collider::getHalfSize() {
    return body.getSize() / 2.0f;
}
