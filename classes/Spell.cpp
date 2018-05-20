#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../headers/Spell.h"
#include "../headers/Settings.h"
#include "../headers/Utils.h"


class Player;


Spell::Spell() {

}

Spell::~Spell() {

}

void Spell::setParams(std::string name, std::string spellType, int manaCost) {
    this->name = name;
    this->spellType = spellType;
    this->manacost = manaCost;
}

void Spell::use() {
    
}


Projectile::Projectile(sf::Texture &texture, sf::Vector2f vel, 
                       float speed, sf::Vector2f pos, float rotation,
                       float scale, void (*callback)(Projectile &projectile, 
                       float dt, sf::Vector2f mousePos)) {
    this->vel = vel;
    this->speed = speed;
    this->func = callback;
    this->rotation = rotation;
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

void Projectile::update(float dt, sf::Vector2f mousePos) {
    (*func)(*this, dt, mousePos);
}

void fireball(Projectile &projectile, float dt, sf::Vector2f mousePos) {
    projectile.move(projectile.vel * (dt / Settings::TIMESCALE));
}

void magicMissile(Projectile &projectile, float dt, sf::Vector2f mousePos) {
    
    //projectile.vel = rotateNormalVect(projectile.vel, (degrees * (M_PI / 180)));
    
    float angle = getAngle(projectile.getPosition(), mousePos);
    projectile.vel = normalizedVec((sf::Vector2f(-sin(angle * (M_PI / 180)), -cos(angle * (M_PI / 180))) / 18.f + projectile.vel) / 2.f);
    projectile.setRotation(180 - atan2(projectile.vel.x, projectile.vel.y) * (180 / M_PI));
    projectile.move(projectile.vel * projectile.speed * (dt / Settings::TIMESCALE));
   
}


void Projectile::draw(sf::RenderWindow &window) {
    window.draw(*this);
}

void Fireball::use() {
    player.addProjectile(Projectile(texture, 
                         normalizedVec(sf::Vector2f(-sin(player.getMouseAngleRad()), -cos(player.getMouseAngleRad()))), 
                         4, player.getPos(), 360 - player.getMouseAngle(), 0.5, &fireball));
}

Fireball::Fireball(Player &player):
    player(player) {
    texture.loadFromFile("./resources/spell_textures/fireball.png");
    setParams("Fireball", "Damage", 20);
    this->player = player;
}

Fireball::~Fireball() {
}

MagicMissile::MagicMissile(Player &player):
    player(player) {
    this->player = player;
    texture.loadFromFile("./resources/spell_textures/magicmissile.png");
    setParams("Magic Missile", "Damage", 8);
}

MagicMissile::~MagicMissile() {
}

void MagicMissile::use() {
    player.addProjectile(Projectile(texture, 
                         normalizedVec(sf::Vector2f(-sin(player.getMouseAngleRad() + M_PI / 2), -cos(player.getMouseAngleRad() + M_PI / 2))), 
                         2, player.getPos(), 270 - player.getMouseAngle(), 0.5, &magicMissile));
    player.addProjectile(Projectile(texture, 
                         normalizedVec(sf::Vector2f(-sin(player.getMouseAngleRad() - M_PI / 2), -cos(player.getMouseAngleRad() - M_PI / 2))), 
                         2, player.getPos(), 450 - player.getMouseAngle(), 0.5, &magicMissile));
    player.addProjectile(Projectile(texture, 
                         normalizedVec(sf::Vector2f(-sin(player.getMouseAngleRad()), -cos(player.getMouseAngleRad()))), 
                         2, player.getPos(), 360 - player.getMouseAngle(), 0.5, &magicMissile));
}



