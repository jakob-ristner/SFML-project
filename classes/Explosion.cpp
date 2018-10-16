#include <SFML/Graphics.hpp>
#include <vector>
#include "../headers/Explosion.h"

Explosion::Explosion(float rad, sf::Vector2f pos,
                     float dmg, float maxDuration, Animation animation) {
    this->rad = rad;
    this->pos = pos;
    this->dmg = dmg;
    this->maxDuration = maxDuration;
    this->animation = animation;
    sf::Texture &text = *(animation.getSheet());
    sprite.setTexture(text);
    sprite.setTextureRect(animation.getTextureRect());
    sprite.setOrigin(animation.getOrigin());
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
    animation.update(dt);
    sprite.setTextureRect(animation.getTextureRect());
    sprite.setOrigin(animation.getOrigin());
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

void Explosion::onCollision(Enemy &enemy) {
    enemy.hurt(dmg);
}

