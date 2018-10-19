#pragma once
#include <SFML/Graphics.hpp>
#include "./Player.h"
#include "./Npc.h"
#include "./Collider.h"
#include "./Animation.h"
#include "./Explosion.h"

class Player;
class Explosion;
class Enemy;
class Buff;
class Spell {
public:
    Spell();
    ~Spell();
    virtual void use();
    int getCastTime();
    void setAnimations(std::vector<Animation> animations);
    void addAnimation(Animation anim);
    float getCooldown();
    float getCooldownTimer();
    virtual void update(float dt);
    bool isReady;
    std::vector<Animation> getAnimations();

    static  std::vector<Explosion> *explosions;
    float getManaCost();
private:

protected:
    std::string spellType;
    std::string name;
    int castTime;
    float cooldown;
    float cooldownTimer;
    float manaCost;
    bool isAnimated = false;
    Animation anim;
    std::vector<Animation> animations;
};

class Buff {
public:
    Buff();
    ~Buff();
    virtual void update(Player &player, float dt);
    virtual void begin(Player &player);
    virtual void end(Player &player);
    bool kill;

protected:
    float counter;
    float duration;
};

class Projectile: public sf::Sprite{
public:
    Projectile(sf::Texture &texture, sf::Vector2f vel,
               float speed, sf::Vector2f pos,
               float rotation, float scale,
               void (*callback)(Projectile &projectile,
               float dt, sf::Vector2f mousePos),
               bool (*onCollide)(Enemy &enemy, Projectile &projectile));
    ~Projectile();
    Projectile();
    void update(float dt, sf::Vector2f mousePos);
    void draw(sf::RenderWindow &window);
    void onCollision(Enemy &enemy);
    void (*func)(Projectile &projectile, float dt, sf::Vector2f mousePos);
    // Will be overloaded for different types of collisions
    bool (*onCollide)(Enemy &enemy, Projectile &projectile);
    bool kill;

    float getSpeed();
    float counter;
    std::vector<Animation> getAnimations();
    

    sf::Vector2f vel;
    SpriteCollider getCollider();

    static std::vector<Explosion> *explosions;

    void setAnimationAtIndex(int index);
    void setAnimations(std::vector<Animation> animations);
    void addAnimation(Animation anim);
    void setTextureSize(sf::IntRect newSize);
private:
    Animation anim;
    std::vector<Animation> animations;
    bool isAnimated = false;
    float speed;
    float rotation;
};

class Fireball: public Spell {
public:
    Fireball(Player &player);
    ~Fireball();
    void use() override;
    void update(float dt) override;

private:
    Player &player;
    sf::Texture texture;

};

class MagicMissile: public Spell {
public:
    MagicMissile(Player &player);
    ~MagicMissile();
    void use() override;
    void update(float dt) override;

private:
    Player &player;
    sf::Texture texture;
};

class Explode: public Spell {
public:
    Explode(Player &player);
    ~Explode();
    void use() override;
    void update(float dt) override;
    Animation animation;
    sf::Texture text;
private:
    int duration;
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
    float speedBuff;
    float playerStartSpeed;

};

class SprintSpell: public Spell {
public:

    SprintSpell(Player &player);
    ~SprintSpell();
    void use() override;
    void update(float dt) override;

private:
    Player &player;
    SprintBuff temp;
    Buff *buff;
    
};

class FlashHeal: public Spell {
public:
    FlashHeal(Player &player);
    ~FlashHeal();
    void use() override;
    void update(float dt) override;

private:
    Player &player;
    float healing;
};
// Firebolt Spell Start
// Firebolt is like fireball except it explodes on collision
class Firebolt: public Spell {
public:
    Firebolt(Player &player);
    ~Firebolt();
    void use() override;
    void update(float dt) override;
private:
    Player &player;
    sf::Texture texture;
    sf::Texture texture2;
};



