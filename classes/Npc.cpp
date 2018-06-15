
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <vector>

#include "../headers/Npc.h"
#include "../headers/Utils.h"
#include "../headers/Settings.h"
#include "../headers/Obstacle.h"
#include "../headers/Player.h"

Enemy::Enemy(sf::Texture &texture, sf::Vector2f pos, 
          sf::Vector2f vel, float moveSpeed, 
          float maxHp, float hitpoints, 
          float attackStrength, 
          float attackSpeed, unsigned int level,
          Player &player):
    player(player) {
    this->vel = vel;
    this->moveSpeed = moveSpeed;
    this->maxHp = maxHp;
    this->hitpoints = hitpoints;
    this->attackStrength = attackStrength;
    this->attackSpeed = attackSpeed;
    this->level = level;

    settings = Settings();
    fric = 1.2;
    acc = sf::Vector2f(0.0f, 0.0f);

    setTexture(texture);
    setOrigin(sf::Vector2f(texture.getSize().x, texture.getSize().y) / 2.0f);
    setPosition(pos);
    hurtTime = 0;

}

Enemy::~Enemy() {

}

float Enemy::getHitpoints() {
    return hitpoints;
}

float Enemy::getMaxHitpoints() {
    return maxHp;
}

float Enemy::hurt(float amount) {
    hitpoints -= amount;
    hurtTime = 100.0f;
}

bool Enemy::isAlive() {
    return hitpoints > 0;
}

sf::Vector2f Enemy::getVel() {
    return vel;
}

SpriteCollider Enemy::getCollider() {
    return SpriteCollider(*this, getVel());
}

Slime::Slime(sf::Texture &texture, sf::Vector2f pos, sf::Vector2f vel, Player &player) :
    Enemy(texture, pos, vel, 0.1f, 10.0f, 10.0f, 2.0f, 500.0f, 1, player) {
}

Slime::Slime(sf::Texture &texture, sf::Vector2f pos, Player &player) :
    Enemy(texture, pos, sf::Vector2f(0.0f, 0.0f), 0.1f, 10.0f, 10.0f, 2.0f, 500.0f, 1, player){

}

Slime::~Slime() {

}

void Slime::update(float dt) {
    acc = sf::Vector2f(0.0f, 0.0f);

    // Here some thinking will be executed (TODO)
    sf::Vector2f direction = player.getPos() - getPosition();
    acc = direction;
    // -----------------------------------

    if(!(acc.x == 0.0f || acc.y == 0.0f)) {
        acc = normalizedVec(acc) * moveSpeed;
    }

    acc += vel / fric;

    vel = acc;
    sf::Vector2f pos = getPosition();
    pos += vel * (dt / settings.TIMESCALE);

    setPosition(pos);
    if (hurtTime > 0) {
        setColor(sf::Color(255, 0, 0));
        hurtTime -= dt;
    } else {
        setColor(sf::Color(255, 255, 255));
    }

}

void Slime::draw(sf::RenderWindow &window) {
    window.draw(*this);
}

EnemyFactory::EnemyFactory(Player &player):
    player(player) {
    sf::Texture slimeTexture;
    slimeTexture.loadFromFile("./resources/enemy_textures/slime.png");
    slimeTexture.setSmooth(true);
    enemyTextures.push_back(slimeTexture);
}

EnemyFactory::~EnemyFactory() {
}

void EnemyFactory::spawnEnemy(std::string enemyType, sf::Vector2f pos) {
    if (enemyType == "slime") {
        enemies.push_back(std::unique_ptr<Enemy>(new Slime(enemyTextures[0], pos, player)));
    }
}

// Updates itself and all belonging enemies
void EnemyFactory::update(float dt) {
    std::vector<int> deadEnemies;
    int i = 0;
    for (auto itr = enemies.begin(); itr != enemies.end(); ++itr, i++) {
        (*itr)->update(dt);
        if (!(*itr)->isAlive()) {
            deadEnemies.push_back(i);
        }
    }
    // Remove dead enemies
    for (i = deadEnemies.size() - 1; i >= 0; i--) {
        enemies.erase(enemies.begin() + deadEnemies[i]);
    }
}

void EnemyFactory::draw(sf::RenderWindow &window) {
    for (auto itr = enemies.begin(); itr != enemies.end(); ++itr) {
        (*itr)->draw(window);
    }
}

// Checks all containing enemies for collision with walls
void EnemyFactory::wallCollide(std::vector<Obstacle> obstacles) {
    sf::Vector2f direction;
    for (Obstacle &obstacle : obstacles) {
        Collider obstacleColl = obstacle.getCollider();
        for (auto itr = enemies.begin(); itr != enemies.end(); ++itr) {
            (*itr)->getCollider().checkCollision(&obstacleColl, direction, 0.0f);
        }
    }
}

void EnemyFactory::hurtEnemy(int i, int amount) {
    (*enemies[i]).hurt(amount);
}

// Checks all belonging enemies for collisions with spells
// and calls the apropriate functions
void EnemyFactory::spellCollide(std::vector<Projectile> &projs) {
    sf::Vector2f direction;
    for (auto itr = enemies.begin(); itr != enemies.end(); ++itr) {
        SpriteCollider currentSprite = (*itr)->getCollider();
        for (Projectile &projectile : projs) {
            SpriteCollider currentSpell = projectile.getCollider();
            if (currentSprite.checkCollision(&currentSpell, direction, 0.0f)) {
                projectile.onCollision(*(itr->get()));
            }
        }
    }
}
