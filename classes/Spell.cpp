#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../headers/Spell.h"
#include "../headers/Settings.h"
#include "../headers/Utils.h"
#include "../headers/Npc.h"


class Player;

Spell::Spell() {

}

Spell::~Spell() {

}

void Spell::setParams(std::string name, std::string spellType,
                      int manaCost) {
    this->name = name;
    this->spellType = spellType;
    this->manacost = manaCost;
    this->castTime = castTime;
}

void Spell::setAnimation(Animation anim) {
    this->anim = anim;
    bool isAnimated = true;
}

void Spell::use() {

}

int Spell::getCastTime() {

}

Projectile::Projectile(sf::Texture &texture, sf::Vector2f vel,
                       float speed, sf::Vector2f pos, float rotation,
                       float scale, void (*callback)(Projectile &projectile,
                       float dt, sf::Vector2f mousePos)) {
    this->vel = vel;
    this->speed = speed;
    this->func = callback;
    this->rotation = rotation;
    kill = false;
    counter = 0;


    setScale(scale, scale);
    setTexture(texture);
    setRotation(rotation);
    setOrigin(sf::Vector2f(texture.getSize().x, texture.getSize().y) / 2.0f);
    setPosition(pos);
}

Projectile::Projectile(sf::Texture &texture, sf::Vector2f vel,
                       float speed, sf::Vector2f pos, float rotation,
                       float scale, void (*callback)(Projectile &projectile,
                       float dt, sf::Vector2f mousePos),
                       bool (*onCollide)(Enemy &enemy)) {
    this->vel = vel;
    this->speed = speed;
    this->func = callback;
    this->rotation = rotation;
    this->onCollide = onCollide;
    kill = false;
    counter = 0;


    setScale(scale, scale);
    setTexture(texture);
    setRotation(rotation);
    setOrigin(sf::Vector2f(texture.getSize().x, texture.getSize().y) / 2.0f);
    setPosition(pos);
}

Projectile::Projectile() {;
}

Projectile::~Projectile() {
}

void Projectile::onCollision(Enemy &enemy) {
    kill = onCollide(enemy);
}

void Projectile::update(float dt, sf::Vector2f mousePos) {
    counter += 1 * (dt / Settings::TIMESCALE);
    (*func)(*this, dt, mousePos);
    if (isAnimated) {
        anim.update(dt);
        setTextureRect(anim.getTextureRect());
    }
}

void Projectile::draw(sf::RenderWindow &window) {
    window.draw(*this);
}

SpriteCollider Projectile::getCollider() {
    return SpriteCollider(*this, vel);
}

void Projectile::setAnimation(Animation anim) {
    this->anim = anim;
    isAnimated = true;
    setTextureRect(anim.getTextureRect());
}

void fireball(Projectile &projectile, float dt, sf::Vector2f mousePos) {
    projectile.move(projectile.vel * projectile.speed * (dt / Settings::TIMESCALE));
}

bool fireballDamage(Enemy &enemy) {
    enemy.hurt(2);
    return true;
}

void magicMissile(Projectile &projectile, float dt, sf::Vector2f mousePos) {
    if (projectile.counter > 1500) {
        projectile.kill = true;
    }
    float angle = getAngle(projectile.getPosition(), mousePos);
    projectile.vel = normalizedVec((sf::Vector2f(-sin(angle * (M_PI / 180)), -cos(angle * (M_PI / 180))) / 18.f + projectile.vel) / 2.f);
    projectile.setRotation(180 - atan2(projectile.vel.x, projectile.vel.y) * (180 / M_PI));
    projectile.move(projectile.vel * projectile.speed * (dt / Settings::TIMESCALE));
}


void Fireball::use() {
    // TODO: Add animation spawning and scaling
    player.addProjectile(Projectile(texture,
                         normalizedVec(sf::Vector2f(-sin(player.getMouseAngleRad()), -cos(player.getMouseAngleRad()))),
                         10,
                         player.getPos(),
                         360 - player.getMouseAngle(),
                         0.5,
                         &fireball,
                         &fireballDamage));
}



Fireball::~Fireball() {
}

int Fireball::getCastTime() {
  return castTime;
}

Fireball::Fireball(Player &player):
    player(player) {
    castTime = 10;
    texture.loadFromFile("./resources/spell_textures/smolfirered.png");
    setParams("Fireball", "Damage", 20);
    this->player = player;
}

MagicMissile::MagicMissile(Player &player):
    player(player) {
    castTime = 4;
    this->player = player;
    texture.loadFromFile("./resources/spell_textures/magicmissile.png");
    setParams("Magic Missile", "Damage", 8);
}

MagicMissile::~MagicMissile() {
}

int MagicMissile::getCastTime() {
  return castTime;
}

bool magicMissileDamage(Enemy &enemy) {
    enemy.hurt(0.5);
    return true;
}

void MagicMissile::use() {
    player.addProjectile(Projectile(texture,
                         normalizedVec(sf::Vector2f(-sin(player.getMouseAngleRad() + M_PI / 2), -cos(player.getMouseAngleRad() + M_PI / 2))),
                         4, player.getPos(), 270 - player.getMouseAngle(), 0.5, &magicMissile, &magicMissileDamage));
    player.addProjectile(Projectile(texture,
                         normalizedVec(sf::Vector2f(-sin(player.getMouseAngleRad() - M_PI / 2), -cos(player.getMouseAngleRad() - M_PI / 2))),
                         4, player.getPos(), 450 - player.getMouseAngle(), 0.5, &magicMissile, &magicMissileDamage));
    player.addProjectile(Projectile(texture,
                         normalizedVec(sf::Vector2f(-sin(player.getMouseAngleRad()), -cos(player.getMouseAngleRad()))),
                         4, player.getPos(), 360 - player.getMouseAngle(), 0.5, &magicMissile, &magicMissileDamage));
}
