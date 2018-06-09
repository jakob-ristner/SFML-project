#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "./Settings.h"
#include "./Collider.h"
#include "./Spell.h"
#include "./UiInterface.h"

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
    void castSpell();
    void update(float dt);
    void setMouseAngle(float angle);
    float getMouseAngle();
    float getMouseAngleRad();
    void setRotation(float rotation);
    void addSpell(Spell *spell);
    Spell *getSpell(int index);
    void onCollision(sf::Vector2f direction);
    Collider getCollider();
    void addProjectile(Projectile projectile);
    std::vector<Projectile> &getProjectiles();
    sf::Vector2f getMousePos();
    void setMousePos(sf::Vector2f pos);
    float castProgress;
    bool casting;
    CastBar uiCastBar;

private:
    sf::Vector2f pos;
    std::vector<Spell *> spellInventory;
    sf::Vector2f vel;
    sf::Vector2f acc;
    sf::RectangleShape body;
    Settings settings;
    int speed;
    int selectedSpell;
    float playeracc = 2;
    float fric = 1.2;
    std::vector<Projectile> projectiles;
    float mouseAngle;
    sf::Vector2f mousePos;
    bool switchedSpells;

};
