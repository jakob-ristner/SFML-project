#include <SFML/Graphics.hpp>
#include <vector>
#include "../headers/Explosion.h"

Explosion::Explosion(float rad, sf::Vector2f pos,
                     float dmg, float maxDuration) {
    this->rad = rad;
    this->pos = pos;
    this->dmg = dmg;
    this->maxDuration = maxDuration;
    duration = 0;
    color = sf::Color(0, 0, 0);
    kill = false;
    body.setRadius(rad);
    body.setFillColor(color);
    body.setPosition(pos);
    active = true;
}

Explosion::Explosion() {

}

Explosion::~Explosion() {

}

void Explosion::update(float dt) {
    duration += dt;
    active = false;
    if (duration > maxDuration) {
        kill = true;
    }
}

void Explosion::draw(sf::RenderWindow &window) {
    window.draw(body);
}

float Explosion::getDamage() {
    return dmg;
}

CollisionCircle Explosion::getCollider() {
    return CollisionCircle(pos, rad);
}


