#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Settings.h"
#include "Collider.h"
#include "Spell.h"

class Projectile;
class Player {
public:
    Player(sf::RectangleShape body);
    Player();
    ~Player();
    sf::Vector2f getPos();
    void setPos(sf::Vector2f);
    void draw(sf::RenderWindow &window);
    void update(float dt);
    void onCollision(sf::Vector2f direction);
    Collider getCollider();
    void addProjectile(Projectile &projectile);

private:
    sf::Vector2f pos;   
    sf::Vector2f vel;
    sf::Vector2f acc;
    sf::RectangleShape body;
    Settings settings;
    int speed;
    float playeracc = 2;
    float fric = 1.2;
    std::vector<sf::Sprite> projectiles;

};
