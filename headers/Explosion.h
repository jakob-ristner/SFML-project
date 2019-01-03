#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "./Collider.h"
#include "./Animation.h"
#include "./Npc.h"
class Enemy;

// Object that represents an explosion triggered by a spell
// Args:
// rad - radius of explosion
// pos - position of explosion
// dmg - damage inflicted by damage
// maxDuration - maximum duration of explosion
// animation - the animation of the explosion
class Explosion {
public:
    Explosion(float rad, sf::Vector2f pos, float dmg, float maxDuration, Animation animation);
    Explosion();
    ~Explosion();

    bool kill;
    bool active;
    float getDamage();
    void draw(sf::RenderWindow &window);
    void update(float dt);
    CollisionCircle getCollider();
    void onCollision(Enemy &enemy);


private:
    float rad;
    float dmg;
    float duration;
    float maxDuration;
    sf::Vector2f pos;
    
    Animation animation;
    sf::Sprite sprite;


    //temporary until animation frames
    sf::CircleShape body;
    sf::Color color;

};
