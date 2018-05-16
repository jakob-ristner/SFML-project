#pragma once
#include <SFML/Graphics.hpp>
#include "../headers/Player.h"

class Player;
class Spell {
public:
    Spell();
    ~Spell();
    virtual void use();
    void setParams(std::string name, std::string spellType, 
                   int manaCost);
    std::string name;
    std::string spellType;
    int manacost;
};

class Projectile: public sf::Sprite{
public:
    Projectile(sf::Texture &texture, sf::Vector2f vel, float speed, sf::Vector2f pos, float rotation);
    ~Projectile();
    Projectile();
    void update(float dt);
    void draw(sf::RenderWindow &window);
    sf::Vector2f vel;
    float speed;
};

class Fireball: public Spell {
public:
    Fireball(Player &player);
    ~Fireball();
    void use() override;
    void check();

private:
    Player &player;
    sf::Texture texture;

};
