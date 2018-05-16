#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Settings.h"
#include "Collider.h"
#include "Spell.h"

class Projectile;
class Spell;
class Player {
public:
    Player(sf::RectangleShape body);
    Player();
    ~Player();
    sf::Vector2f getPos();
    void setPos(sf::Vector2f);
    void draw(sf::RenderWindow &window);
    void castSpell(int index);
    void update(float dt);
    void setMouseAngle(float angle);
    float getMouseAngle();
    float getMouseAngleRad();
    void addSpell(Spell *spell);
    Spell *getSpell(int index);
    void onCollision(sf::Vector2f direction);
    Collider getCollider();
    void addProjectile(Projectile projectile);
    std::vector<Projectile> &getProjectiles();
    

private:
    sf::Vector2f pos;   
    std::vector<Spell *> spellInventory;
    sf::Vector2f vel;
    sf::Vector2f acc;
    sf::RectangleShape body;
    Settings settings;
    int speed;
    float playeracc = 2;
    float fric = 1.2;
    std::vector<Projectile> projectiles;
    float mouseAngle;

};
