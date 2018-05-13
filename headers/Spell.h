#pragma once
#include <SFML/Graphics.hpp>
#include "../headers/Player.h"

class Player;
class Spell {
public:
    Spell();
    ~Spell();
    void setParams(std::string name, std::string spellType, 
                   int manaCost, sf::Texture texture);
    std::string name;
    std::string spellType;
    int manacost;
    sf::Texture texture;
};

class Projectile: public sf::Sprite{
public:
    Projectile(sf::Texture &texture, sf::Vector2f vel, float speed);
    ~Projectile();
    void update(float dt);
    void draw(sf::RenderWindow window);
    sf::Texture texture;
    sf::Vector2f vel;
    float speed;
};

class Fireball: public Spell {
public:
    Fireball();
    ~Fireball();
    void use(sf::Vector2f origin);
};
