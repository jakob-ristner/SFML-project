#pragma once
#include <SFML/Graphics.hpp>

class Spell {
public:
    Spell();
    ~Spell();
    void setParams(std::string name, std::string spellType, int manaCost);
    std::string name;
    std::string spellType;
    int manacost;
};

class Fireball: public Spell {
public:
    Fireball();
    ~Fireball();

};