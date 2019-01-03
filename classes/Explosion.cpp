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
    text.setRepeated(true);
    sprite.setTexture(text);
    sprite.setTextureRect(animation.getTextureRect());
    sprite.setOrigin(animation.getOrigin());
    float scale = 2 * rad / animation.getTextureRect().width;
    sprite.setScale(scale, scale);
    duration = 0;
    color = sf::Color(0, 0, 0);
    kill = false;
    active = true;
}

Explosion::Explosion() {

}

Explosion::~Explosion() {

}

// Updates the internal state
// Args:
// dt - time since last update
void Explosion::update(float dt) {
    duration += dt;
    animation.update(dt);
    sprite.setTextureRect(animation.getTextureRect());
    //sprite.setOrigin(animation.getOrigin());
    sprite.setPosition(pos);
    active = false;
    
    if (duration > maxDuration) {
        kill = true;
   }
}

void Explosion::draw(sf::RenderWindow &window) {
    window.draw(sprite);
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

