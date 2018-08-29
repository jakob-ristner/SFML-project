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
    
void Spell::use() {

}
int Spell::getCastTime() {
}

void Spell::update(float dt) {
    
}

Buff::Buff() {

}

Buff::~Buff() {

}

void Buff::begin(Player &player) {
    
}

void Buff::end(Player &player) {

}

void Buff::update(Player &player, float dt) {

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
    this->func = callback; // TODO rename callback to update funcition or something
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

float Projectile::getSpeed() {
    return speed;
}

void Projectile::onCollision(Enemy &enemy) {
    kill = onCollide(enemy);
}

void Projectile::update(float dt, sf::Vector2f mousePos) {
    counter += 1 * (dt / Settings::TIMESCALE);
    (*func)(*this, dt, mousePos);
}

SpriteCollider Projectile::getCollider() {
    return SpriteCollider(*this, vel);
}




void Projectile::draw(sf::RenderWindow &window) {
    window.draw(*this);
}

//Fireball Spell Start//
Fireball::Fireball(Player &player):
    player(player) {
      castTime = 10;
    texture.loadFromFile("./resources/spell_textures/fireball.png");
    setParams("Fireball", "Damage", 20);
    this->player = player;
    cooldown = 2000;
    cooldownTimer = 0;
    isReady = true;
}

Fireball::~Fireball() {
}

void Fireball::update(float dt) {
    if (cooldownTimer < cooldown) {
        cooldownTimer += dt;
    } else {
        isReady = true;
        
    }
    
}

bool fireballDamage(Enemy &enemy) {
    enemy.hurt(2);
    return true;
}

void fireball(Projectile &projectile, float dt, sf::Vector2f mousePos) {
    // The update function for the projectiles created with the fireball spell
    projectile.move(projectile.vel * projectile.getSpeed() * (dt / Settings::TIMESCALE));
}

void Fireball::use() {
    player.addProjectile(Projectile(texture,
                         normalizedVec(sf::Vector2f(-sin(player.getMouseAngleRad()), -cos(player.getMouseAngleRad()))),
                         10,
                         player.getPos(),
                         360 - player.getMouseAngle(),
                         0.5,
                         &fireball,
                         &fireballDamage));
    isReady = false;
    cooldownTimer = 0;
}

int Fireball::getCastTime() {
  return castTime;
}
//FireBall Spell End//

//MagicMissile Spell Start//
MagicMissile::MagicMissile(Player &player):
    player(player) {
    castTime = 4;
    this->player = player;
    texture.loadFromFile("./resources/spell_textures/magicmissile.png");
    setParams("Magic Missile", "Damage", 8);
    cooldown = 60;
    cooldownTimer = 0;
    isReady = true;
};

MagicMissile::~MagicMissile() {

}

void MagicMissile::update(float dt) {
    if (cooldownTimer < cooldown) {
        cooldownTimer += dt;
    } else {
        isReady = true;
        
    }
}

bool magicMissileDamage(Enemy &enemy) {
    enemy.hurt(0.5);
    return true;
}

void magicMissile(Projectile &projectile, float dt, sf::Vector2f mousePos) {
    // The update function for the projectiles created with the magicmissile spell
    if (projectile.counter > 1500) {
        projectile.kill = true;
    }
    float angle = getAngle(projectile.getPosition(), mousePos);

    projectile.vel = normalizedVec((sf::Vector2f(-sin(angle * (M_PI / 180)), -cos(angle * (M_PI / 180))) / 18.f + projectile.vel) / 2.f);
    projectile.setRotation(180 - atan2(projectile.vel.x, projectile.vel.y) * (180 / M_PI));
    projectile.move(projectile.vel * projectile.getSpeed() * (dt / Settings::TIMESCALE));
    // These lines of math basically make the projectile follow the mouse by rotating towards it
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
    isReady = false;
    cooldownTimer = 0;
}


int MagicMissile::getCastTime() {
  return castTime;
}
//MagicMissile Spell End//

//SprintSpell Spell Start//

SprintSpell::SprintSpell(Player &player):
player(player) {
    castTime  = 0;
    this->player = player;
    setParams("Sprint", "Buff", 20);
    cooldown = 1000;
    cooldownTimer = 0;
    isReady = true;
}

SprintSpell::~SprintSpell() {

}

void SprintSpell::use() {
    temp = SprintBuff(player);
    buff = &temp;
    player.addBuff(buff);
    isReady = false;
    cooldownTimer = 0;
}

void SprintSpell::update(float dt) {
    if (cooldownTimer < cooldown) {
        cooldownTimer += dt;
    } else {
        isReady = true;
    }
}

int SprintSpell::getCastTime() {
    return castTime;
}

SprintBuff::SprintBuff(Player &player) {
    counter = 0;
    duration = 1000;
    speedBuff = 2;
    kill = false;

}

SprintBuff::SprintBuff() {
    
}

SprintBuff::~SprintBuff() {

}

void SprintBuff::update(Player &player, float dt) {
    if (counter < duration) {
        counter += dt;
    } else {
        kill = true;
    }
}

void SprintBuff::begin(Player &player) {
    playerStartSpeed = player.getSpeed();
    player.setMoveSpeed(speedBuff + playerStartSpeed);
}

void SprintBuff::end(Player &player) {
    player.setMoveSpeed(playerStartSpeed);
}


//SprintSpell Spell End//
