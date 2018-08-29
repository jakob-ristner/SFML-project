#pragma once
#include <SFML/Graphics.hpp>
#include "./Player.h"
#include "./Npc.h"
#include "./Collider.h"

class Player;
class Enemy;
class Buff;
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
    virtual int getCastTime();
    virtual void update(float dt);
    bool isReady;

protected:
    int castTime;
    float cooldown;
    float cooldownTimer;
};

class Buff {
public:
    Buff();
    ~Buff();
    virtual void update(Player &player, float dt);
    virtual void begin(Player &player);
    virtual void end(Player &player);

private:
    float counter;

};

class Projectile: public sf::Sprite{
public:
    Projectile(sf::Texture &texture, sf::Vector2f vel,
               float speed, sf::Vector2f pos,
               float rotation, float scale,
               void (*callback)(Projectile &projectile,
               float dt, sf::Vector2f mousePos));
    Projectile(sf::Texture &texture, sf::Vector2f vel,
               float speed, sf::Vector2f pos,
               float rotation, float scale,
               void (*callback)(Projectile &projectile,
               float dt, sf::Vector2f mousePos),
               bool (*onCollide)(Enemy &enemy));
    ~Projectile();
    Projectile();
    void update(float dt, sf::Vector2f mousePos);
    void draw(sf::RenderWindow &window);
    void onCollision(Enemy &enemy);
    void (*func)(Projectile &projectile, float dt, sf::Vector2f mousePos);
    // Will be overloaded for different types of collisions
    bool (*onCollide)(Enemy &enemy);
    bool kill;

    float getSpeed();
    float counter;
    

    sf::Vector2f vel;
    SpriteCollider getCollider();

private:
    float speed;
    float rotation;


};

class Fireball: public Spell {
public:
    Fireball(Player &player);
    ~Fireball();
    void use() override;
    int getCastTime() override;
    void update(float dt) override;

private:
    int castTime;
    Player &player;
    sf::Texture texture;

};

class MagicMissile: public Spell {
public:
    MagicMissile(Player &player);
    ~MagicMissile();
    void use() override;
    int getCastTime() override;
    void update(float dt) override;

private:
    int castTime;
    Player &player;
    sf::Texture texture;
};

class SprintBuff: public Buff {
public:
    SprintBuff();
    SprintBuff(Player &player);
    ~SprintBuff();
    void update(Player &player, float dt) override;
    void begin(Player &player) override;
    void end(Player &player) override;



private:
    float counter;
    float duration;
    float speedBuff;
    float playerStartSpeed;

};

class SprintSpell: public Spell {
public:

    SprintSpell(Player &player);
    ~SprintSpell();
    void use() override;
    int getCastTime();
    void update(float dt) override;

private:
    int castTime;
    Player &player;
    SprintBuff temp;
    Buff *buff;
    
};

