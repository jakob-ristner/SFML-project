#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/Spell.h"


class Player;

Spell::Spell() {

}
Spell::~Spell() {

}

void Spell::setParams(std::string name, std::string spellType, int manaCost, sf::Texture texture) {
    //this->name = name;
    this->spellType = spellType;
    this->manacost = manaCost;
    this->texture = texture;
}


Projectile::Projectile(sf::Texture &texture, sf::Vector2f vel, float speed) {
    this->texture = texture;
    this->vel = vel;
    this->speed = speed;
    setTexture(this->texture);
}

Projectile::~Projectile() {

}


Fireball::Fireball() {
    sf::Texture texture = sf::Texture();
    texture.loadFromFile("../resources/fireball.png");
    setParams("Fireball", "Damage", 20, texture);
}

Fireball::~Fireball() {

}

void Fireball::use(sf::Vector2f origin) {

}



