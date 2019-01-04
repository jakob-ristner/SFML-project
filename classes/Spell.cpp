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

// Sets the animation vector of the spell. This is used for spells which for 
// example first has an animation while traveling, then an animation when 
// exploding on impact
void Spell::setAnimations(std::vector<Animation> animations) {
    this->animations = animations;
    bool isAnimated = true;
}

// Alias for animations.push_back
void Spell::addAnimation(Animation anim) {
    animations.push_back(anim);
    bool isAnimated = true;
}

// Used for debugging purposes
void printIntRect(sf::IntRect r) {
    std::cout << r.left << r.top << r.width << r.height << std::endl;
}

void Spell::use() {

}

int Spell::getCastTime() {
    return castTime;
}

std::vector<Animation> Spell::getAnimations() {
    return animations;
}

void Spell::update(float dt) {
    
}

float Spell::getManaCost() {
    return manaCost;
}

float Spell::getCooldown() {
    return cooldown;
}

float Spell::getCooldownTimer() {
    return cooldownTimer;
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
                       float dt, sf::Vector2f mousePos),
                       bool (*onCollide)(Enemy &enemy, Projectile &projectile)) {
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


Projectile::Projectile() {;
}

Projectile::~Projectile() {
}

std::vector<Explosion> *Projectile::explosions;

float Projectile::getSpeed() {
    return speed;
}

std::vector<Animation> Projectile::getAnimations() {
    return animations;
}

void Projectile::onCollision(Enemy &enemy) {
    kill = onCollide(enemy, *this);
}

// Updates the internal state of a projectile
// Args:
// dt       - time since last update
// mousePos - the position of the mouse in the game world
void Projectile::update(float dt, sf::Vector2f mousePos) {
    counter += 1 * (dt / settings.TIMESCALE);
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

// Switches the projectiles animation to the one at a given index
void Projectile::setAnimationAtIndex(int index) {
    anim = animations[index];
    isAnimated = true;
    setTextureRect(anim.getTextureRect());
    setTextureSize(anim.getTextureRect());
}

void Projectile::setAnimations(std::vector<Animation> animations) {
    this->animations = animations;
    isAnimated = true;
}

void Projectile::addAnimation(Animation anim) {
    animations.push_back(anim);
    isAnimated = true;
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
    addAnimation(Animation(texture, sf::Vector2f(32, 32), 400, 0, 7, 0));
    anim = animations[0];
    this->player = player;
    cooldown = 2000;
    cooldownTimer = cooldown;
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

bool fireballDamage(Enemy &enemy, Projectile &projectile) {
    enemy.hurt(2);
    return true;
}
void fireball(Projectile &projectile, float dt, sf::Vector2f mousePos) {
    // The update function for the projectiles created with the fireball spell
    projectile.move(projectile.vel * projectile.getSpeed() * (dt / settings.TIMESCALE));
}

void Fireball::use() {
    player.addProjectile(Projectile(texture,
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
    proj.addAnimation(anim);
    proj.setAnimationAtIndex(0);

}

//FireBall Spell End//

//MagicMissile Spell Start//
MagicMissile::MagicMissile(Player &player):
    player(player) {
    castTime = 4;
    this->player = player;
    texture.loadFromFile("./resources/spell_textures/magicmissile.png");
    cooldown = 1000;
    cooldownTimer = cooldown;
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

bool magicMissileDamage(Enemy &enemy, Projectile &projectile) {
    enemy.hurt(0.5);
    return true;
}

void magicMissile(Projectile &projectile, float dt, sf::Vector2f mousePos) {
    // The update function for the projectiles created with the magicmissile spell
    if (projectile.counter > 1500) {
        projectile.kill = true;
    }
    float angle = getAngle(projectile.getPosition(), mousePos);

    projectile.vel = normalizedVec((sf::Vector2f(-sin(angle * (M_PI / 180)), -cos(angle * (M_PI / 180))) / 18.f + projectile.vel) / 0.5f * dt);
    projectile.setRotation(180 - atan2(projectile.vel.x, projectile.vel.y) * (180 / M_PI));
    projectile.move(projectile.vel * projectile.getSpeed() * (dt / settings.TIMESCALE));
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

//MagicMissile Spell End//

//Explode Spell Start//

Explode::Explode(Player &player):
player(player) {
    castTime = 5;
    this->player = player;
    texture.loadFromFile("./resources/spell_textures/explosion1.png");
    texture.setRepeated(true);
    cooldown = 100;
    duration = 500;
    addAnimation(Animation(texture, sf::Vector2f(40, 40), 500, 0, 6, 0));
    anim = animations[0];
    cooldownTimer = cooldown;
    isReady = true;
    name = "Explode";
    spellType = "Damage";
    manaCost = 10;
}

Explode::~Explode() {
    
}

void Explode::use() {

    (*explosions).push_back(Explosion(100, player.getPos(), 2, duration, anim));

    cooldownTimer = 0;
    isReady = false;
}


void Explode::update(float dt) {
    if (cooldownTimer < cooldown) {
        cooldownTimer += dt;
    } else {
        isReady = true;
    }
}

//Explode Spell End//

//SprintSpell Spell Start//

SprintSpell::SprintSpell(Player &player):
player(player) {
    castTime  = 0;
    this->player = player;
    cooldown = 1000;
    cooldownTimer = cooldown;
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

//FlashHeal Spell Start//
FlashHeal::FlashHeal(Player &player):
player(player){
    castTime  = 10;
    this->player = player;
    cooldown = 3000;
    cooldownTimer = cooldown;
    isReady = true;
    name = "Flash Heal";
    spellType = "Heal";
    healing = 20;
}

FlashHeal::~FlashHeal() {

}

void FlashHeal::use() {
    player.heal(healing);
    cooldownTimer = 0;
    isReady = false;
}

void FlashHeal::update(float dt) {
    if (cooldownTimer < cooldown) {
        cooldownTimer += dt;
    } else {
        isReady = true;
    }
}
//FlashHeal Spell End//
//Firebolt Spell Start//
Firebolt::Firebolt(Player &player):
player(player){

    this->player = player;

    texture.loadFromFile("./resources/spell_textures/altfire.png");
    texture2.loadFromFile("./resources/spell_textures/explosion1.png");
    texture.setRepeated(true);
    texture2.setRepeated(true);

    //auto tmpanim1 = Animation(texture, sf::Vector2f(32, 32), 400, 0, 7, 0);
    //auto tmpanim2 = Animation(texture2, sf::Vector2f(40, 40), 500, 0, 6, 0 );
    setAnimations(std::vector<Animation> {
    Animation(texture, sf::Vector2f(32, 32), 400, 0, 7, 0), 
    Animation(texture2, sf::Vector2f(40, 40), 500, 0, 6, 0 )});  
    anim = animations[0];

    castTime = 10;
    cooldown = 10000;
    manaCost = 40;
    cooldownTimer = cooldown;

    name = "Firebolt";
    spellType = "Damage";

    isReady = true; 
}

Firebolt::~Firebolt() {

}


void Firebolt::update(float dt) {
    if (cooldownTimer < cooldown) {
        cooldownTimer += dt;
    } else {
        isReady = true;      
    }
}

bool fireboltDamage(Enemy &enemy, Projectile &projectile) {
    enemy.hurt(3);
    //auto anim = projectile.getAnimations()[0];
    (*projectile.explosions).push_back(Explosion(50, projectile.getPosition(), 
    2, 500, projectile.getAnimations()[1]));
    
    return true;
    
}

void firebolt(Projectile &projectile, float dt, sf::Vector2f mousPos) {
    projectile.move(projectile.vel * projectile.getSpeed() * (dt));
}

void Firebolt::use() {
    player.addProjectile(Projectile(texture, 
    normalizedVec(sf::Vector2f(-sin(player.getMouseAngleRad()), 
    -cos(player.getMouseAngleRad()))), 5, player.getPos(), 
    360 - player.getMouseAngle(), 2, &fireball, &fireboltDamage));
    
    isReady = false;
    cooldownTimer = 0;

    Projectile &proj = player.getProjectiles().back();
    proj.addAnimation(animations[0]);
    proj.addAnimation(animations[1]);
    proj.setAnimationAtIndex(0);
    
}


