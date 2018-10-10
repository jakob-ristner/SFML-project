#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "./Collider.h"

class Explosion {
public:
    Explosion(float rad, sf::Vector2f pos, float dmg, float maxDuration);
    Explosion();
    ~Explosion();

    bool kill;
    bool active;
    float getDamage();
    void draw(sf::RenderWindow &window);
    void update(float dt);
    CollisionCircle getCollider();


private:
    float rad;
    float dmg;
    float duration;
    float maxDuration;
    sf::Vector2f pos;
    

    //temporary until animation frames
    sf::CircleShape body;
    sf::Color color;

};
