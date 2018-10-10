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





std::vector<Explosion> *Spell::explosions;

void Spell::setAnimation(Animation anim) {
    this->anim = anim;
    bool isAnimated = true;
}

void printIntRect(sf::IntRect r) {
    std::cout << r.left << r.top << r.width << r.height << std::endl;
}

void Spell::use() {

}

int Spell::getCastTime() {

}

void Spell::update(float dt) {
    
}

float Spell::getManaCost() {
    return manaCost;
}

float Spell::getCooldown() {

}

float Spell::getCooldownTimer() {

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
    setOrigin(sf::Vector2f(getTextureRect().width, getTextureRect().height) / 2.0f);
    setPosition(pos);
}

Projectile::Projectile(sf::Texture &texture, sf::IntRect textSize, 
                       sf::Vector2f vel,
                       float speed, sf::Vector2f pos, float rotation,
                       float scale, void (*callback)(Projectile &projectile,
                       float dt, sf::Vector2f mousePos),
                       bool (*onCollide)(Enemy &enemy)) :
                       Projectile(texture, vel, speed, pos, rotation, scale, callback, onCollide) {
    
    setTextureSize(textSize);
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
    if (isAnimated) {
        anim.update(dt);
        setTextureRect(anim.getTextureRect());
    }
    sf::FloatRect fl = getGlobalBounds();
}

void Projectile::draw(sf::RenderWindow &window) {
    window.draw(*this);
}

void Projectile::setAnimation(Animation anim) {
    this->anim = anim;
    isAnimated = true;
    setTextureSize(anim.getTextureRect());
}

void Projectile::setTextureSize(sf::IntRect newSize) {
    setTextureRect(newSize);
    setOrigin(sf::Vector2f(newSize.width, newSize.height) / 2.0f);
}

SpriteCollider Projectile::getCollider() {
    return SpriteCollider(*this, vel);
}

//Fireball Spell Start//
Fireball::Fireball(Player &player):
    player(player) {
      castTime = 10;
    texture.loadFromFile("./resources/spell_textures/altfire.png");
    texture.setRepeated(true);
    anim = Animation(texture, sf::Vector2f(32, 32), 400, 0, 7, 0);
    this->player = player;
    cooldown = 2000;
    cooldownTimer = 0;
    isReady = true;
    name = "Fireball";
    spellType = "Damage";
    manaCost = 20;
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
    player.addProjectile(Projectile(texture, anim.getTextureRect(),
                         normalizedVec(sf::Vector2f(-sin(player.getMouseAngleRad()), -cos(player.getMouseAngleRad()))),
                         5,
                         player.getPos(),
                         360 - player.getMouseAngle(),
                         2,
                         &fireball,
                         &fireballDamage));

    isReady = false;
    cooldownTimer = 0;
    Projectile &proj = player.getProjectiles().back();
    proj.setTextureRect(anim.getTextureRect());
    proj.setAnimation(anim);

}

int Fireball::getCastTime() {
  return castTime;
}

float Fireball::getCooldown() {
    return cooldown;
}

float Fireball::getCooldownTimer() {
    return cooldownTimer;
}


//FireBall Spell End//

//MagicMissile Spell Start//
MagicMissile::MagicMissile(Player &player):
    player(player) {
    castTime = 4;
    this->player = player;
    texture.loadFromFile("./resources/spell_textures/magicmissile.png");
    cooldown = 1000;
    cooldownTimer = 0;
    isReady = true;
    name = "Magic Missile";
    spellType = "Damage";
    manaCost = 8;
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

float MagicMissile::getCooldown() {
    return cooldown;
}

float MagicMissile::getCooldownTimer() {
    return cooldownTimer;
}



//MagicMissile Spell End//

//Explode Spell Start//

Explode::Explode(Player &player):
player(player) {
    castTime = 5;
    this->player = player;
    cooldown = 100;
    cooldownTimer = 0;
    isReady = true;
    name = "Explode";
    spellType = "Damage";
    manaCost = 10;
}

Explode::~Explode() {
    
}

void Explode::use() {

    (*explosions).push_back(Explosion(100, sf::Vector2f(player.getPos().x - 100, player.getPos().y - 100), 2, 1000));

    cooldownTimer = 0;
    isReady = false;
}

int Explode::getCastTime() {
    return castTime;
}

void Explode::update(float dt) {
    if (cooldownTimer < cooldown) {
        cooldownTimer += dt;
    } else {
        isReady = true;
    }
}

float Explode::getCooldownTimer() {
    return cooldownTimer;
}

float Explode::getCooldown() {
    return cooldown;
}


//Explode Spell End//

//SprintSpell Spell Start//

SprintSpell::SprintSpell(Player &player):
player(player) {
    castTime  = 0;
    this->player = player;
    cooldown = 1000;
    cooldownTimer = 0;
    isReady = true;
    name = "Sprint";
    spellType = "Buff";
    manaCost = 30;
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

float SprintSpell::getCooldown() {
    return cooldown;
}

float SprintSpell::getCooldownTimer() {
    return cooldownTimer;
}

//SprintSpell Spell End//
