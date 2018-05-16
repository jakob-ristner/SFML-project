#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../headers/Spell.h"
#include "../headers/Settings.h"


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
                       float scale, void (*callback)(Projectile &projectile)) {
    this->vel = vel * speed;
    this->func = callback;
    //(*func)(*this);

    
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

void Projectile::fireball() {
    std::cout << "hej" << std::endl;
} 

void Projectile::update(float dt) {
    //move(vel * (dt / Settings::TIMESCALE));
    (*func)(*this);
}

void fireball(Projectile &projectile) {
    projectile.move(projectile.vel);
}

void Projectile::draw(sf::RenderWindow &window) {
    window.draw(*this);
}

void Fireball::use()  {
    player.addProjectile(Projectile(texture, 
                         sf::Vector2f(-sin(player.getMouseAngleRad()), -cos(player.getMouseAngleRad())), 
                         4, player.getPos(), 360 - player.getMouseAngle(), 0.5,&fireball));
}

Fireball::Fireball(Player &player):
    player(player) {
    texture.loadFromFile("./resources/fireball.png");
    setParams("Fireball", "Damage", 20);
    this->player = player;
}

Fireball::~Fireball() {
   
}



