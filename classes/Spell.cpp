#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/Spell.h"

#pragma region SpellClass
Spell::Spell() {

}
Spell::~Spell() {

}

void Spell::setParams(std::string name, std::string spellType, int manaCost) {
    this->name = name;
    this->spellType = spellType;
    this-> manacost = manaCost;
}
#pragma endregion

#pragma region Fireball

Fireball::Fireball() {
   setParams("Fireball", "Damage", 20);
   std::cout << name << std::endl;
}

Fireball::~Fireball() {

}
#pragma endregion