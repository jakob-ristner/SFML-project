#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "./Settings.h"
#include "./Collider.h"
#include "./Spell.h"
#include "./UiInterface.h"

class Projectile;
class Buff;
class Spell;
class Player {
public:
    Player(sf::RectangleShape body);
    Player();
    ~Player();
    sf::Vector2f getPos();
    void setPos(sf::Vector2f);
    void setVel(sf::Vector2f);
    void draw(sf::RenderWindow &window);
    void castSpell();
    void update(float dt);

    void setMouseAngle(float angle);
    float getMouseAngle();
    float getMouseAngleRad();
    sf::Vector2f getMousePos();
    void setMousePos(sf::Vector2f pos);
    
    void addSpell(Spell *spell);
    Spell *getSpell(int index);

    void addBuff(Buff *buff);

    void onCollision(sf::Vector2f direction);
    Collider getCollider();
    void addProjectile(Projectile projectile);
    void clearProjectiles();


    void hurt(float amount);
    void heal(float amount);
    void setHp(float amount);
    void setMaxHp(float amount);
    void spendMana(float amount);
    void restoreMana(float amount);
    void setMana(float amount);
    void setMaxMana(float amount);
    void setLevel(int newLevel);

    int getLevel();
    std::vector<Projectile> &getProjectiles();
    float getMaxHp();
    float getSpeed();
    
    float castProgress;
    bool casting;
    CastBar uiCastBar;
    SpellBar *spellBar;

    void setHpBar(PlayerHpBar *bar);
    void setManaBar(PlayerManaBar *bar);
    void setLevelIcon(PlayerLevelIcon *icon);
    void setMoveSpeed(float newSpeed);
    void setSpeedMult(float newMult);

    std::vector<Spell *> getSpells();

private:
    sf::Vector2f pos;
    std::vector<Spell *> spellInventory;
    sf::Vector2f vel;
    sf::Vector2f acc;
    sf::RectangleShape body;
    Settings settings;
    int selectedSpell;
    float speedMult;
    float playeracc;
    float originalPlayerAcc;
    float fric;
    std::vector<Projectile> projectiles;
    std::vector<Buff*> buffs;

    float mouseAngle;
    sf::Vector2f mousePos;
    bool switchedSpells;

    float hitpoints;
    float maxHp;
    float mana;
    float maxMana;
    // Should be amount per second
    float manaRegen;
    float timeSinceHurt;
    int level;


    PlayerHpBar *hpBar;
    PlayerManaBar *manaBar;
    PlayerLevelIcon *levelIcon;
};
