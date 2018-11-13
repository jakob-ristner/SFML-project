#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "./Settings.h"
#include "./Obstacle.h"
#include "./Collider.h"
#include "./Player.h"
#include "./Spell.h"
#include "./Explosion.h"
#include "./Pathfinder.h"
#include "./TileMap.h"

class Player;
class Projectile;

// Abstract class serving as superclass for all enemies.
// Different types of enemies will have their own classes.
// Args:
// texture - The texture
// pos - Initial position of the enemy
// vel - Initial velocity of the enemy
// moveSpeed - Scalar for the speed of the enemy
// maxHp - maximum hitpoints for the enemy
// hitpoints - Initial hitpoints of the enemy
class Enemy: public sf::Sprite {
public:
    Enemy(sf::Texture &texture, sf::Vector2f pos, 
          sf::Vector2f vel, float moveSpeed, 
          float maxHp, float hitpoints, 
          float attackStrength,
          float attackSpeed, unsigned int level, 
          Player &player);
    ~Enemy();

    virtual void update(float dt){};
    virtual void draw(sf::RenderWindow &window){};

    sf::Vector2f getVel();

    float getHitpoints();
    float getMaxHitpoints(); float hurt(float amount);
    float getAttackStr();

    unsigned int getLevel();

    bool isAlive();
    bool canAttack();

    void resetAttackTimer();
    void setPathfinder(EnemyPathfinder pathfinder);

    SpriteCollider getCollider();

protected:
    float maxHp;
    float hitpoints;

    float moveSpeed;
    float fric;

    float attackStrength;
    float attackSpeed;
    float timeToAttack; // Updating is done by subclasses

    float hurtTime;

    Settings settings;

    unsigned int level;

    sf::Vector2f vel;
    sf::Vector2f acc;

    Player &player;
    EnemyPathfinder pathfinder;
};

class Slime: public Enemy {
public:
    Slime(sf::Texture &texture, sf::Vector2f pos, sf::Vector2f vel, Player &player);
    Slime(sf::Texture &texture, sf::Vector2f pos, Player &player);
    ~Slime();

    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;
};

// Factory class producing all enemies.
// Handles collision, updating and drawing for all enemies
class EnemyFactory {
public:
    EnemyFactory(Player &player, TileMap &map);
    ~EnemyFactory();

    void spawnEnemy(std::string enemyType, sf::Vector2f pos);
    void update(float dt);
    void draw(sf::RenderWindow &window);
    void hurtEnemy(int i, int amount);

    void wallCollide(std::vector<Obstacle> obstacles);
    void spellCollide(std::vector<Projectile> &projs);
    void playerCollide(Player &player);
    void explosionCollide(std::vector<Explosion> &explosions);

    sf::Vector2f getEnemy(int index);

private:
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<sf::Texture> enemyTextures;
    std::vector<EnemyPathfinder> enemyPathfinders;

    Player &player;
};
