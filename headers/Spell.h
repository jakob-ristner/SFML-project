#pragma once
#include <SFML/Graphics.hpp>
#include "./Player.h"
#include "./Npc.h"
#include "./Collider.h"
#include "./Animation.h"

class Player;
class Enemy;
class Spell {
public:
    Spell();
    ~Spell();
    virtual void use();
    void setParams(std::string name, std::string spellType,
                   int manaCost);
    void setAnimation(Animation anim);
    std::string name;
    std::string spellType;
    int manacost;
    virtual int getCastTime();
    int castTime;

protected:
    Animation anim;
    bool isAnimated = false;
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
    Projectile(sf::Texture &texture, sf::IntRect textSize, sf::Vector2f vel,
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

    void setAnimation(Animation anim);
    void setTextureSize(sf::IntRect newSize);
private:
    Animation anim;
    bool isAnimated = false;
    float speed;
    float rotation;
};

class Fireball: public Spell {
public:
    Fireball(Player &player);
    ~Fireball();
    void use() override;
    int castTime;
    int getCastTime() override;

private:
    Player &player;
    sf::Texture texture;

};

class MagicMissile: public Spell {
public:
    MagicMissile(Player &player);
    ~MagicMissile();
    void use() override;
    int castTime;
    int getCastTime() override;

private:
    Player &player;
    sf::Texture texture;
};
