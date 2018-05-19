
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <vector>

#include "../headers/Npc.h"
#include "../headers/Utils.h"
#include "../headers/Settings.h"

Enemy::Enemy(sf::Texture &texture, sf::Vector2f pos, 
          sf::Vector2f vel, float moveSpeed, 
          float maxHp, float hitpoints, 
          float attackStrength, 
          float attackSpeed, unsigned int level) {
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


}

Enemy::~Enemy() {

}

float Enemy::getHitpoints() {
    return hitpoints;
}

float Enemy::getMaxHitpoints() {
    return maxHp;
}


Slime::Slime(sf::Texture &texture, sf::Vector2f pos, sf::Vector2f vel) :
    Enemy(texture, pos, vel, 1.0f, 10.0f, 10.0f, 2.0f, 500.0f, 1) {
}

Slime::Slime(sf::Texture &texture, sf::Vector2f pos) :
    Enemy(texture, pos, sf::Vector2f(0.0f, 0.0f), 1.0f, 10.0f, 10.0f, 2.0f, 500.0f, 1) {
}

Slime::~Slime() {

}

void Slime::update(float dt) {
    acc = sf::Vector2f(0.0f, 0.0f);

    // Here some thinking will be executed (TODO)
    //
    //
    // -----------------------------------

    if(!(acc.x == 0.0f || acc.y == 0.0f)) {
        acc = normalizedVec(acc) * moveSpeed;
    }

    acc += vel / fric;

    vel = acc;
    sf::Vector2f pos = getPosition();
    pos += vel * (dt / settings.TIMESCALE);

    setPosition(pos);

}

void Slime::draw(sf::RenderWindow &window) {
    window.draw(*this);
}

EnemyFactory::EnemyFactory() {
    sf::Texture slimeTexture;
    slimeTexture.loadFromFile("./resources/enemy_textures/slime.png");
    enemyTextures.push_back(slimeTexture);
}

EnemyFactory::~EnemyFactory() {
}

void EnemyFactory::spawnEnemy(std::string enemyType, sf::Vector2f pos) {
    if (enemyType == "slime") {
        enemies.push_back(std::unique_ptr<Enemy>(new Slime(enemyTextures[0], pos)));
    }
}

void EnemyFactory::update(float dt) {
    for (auto itr = enemies.begin(); itr != enemies.end(); ++itr) {
        (*itr)->update(dt);
    }
}

void EnemyFactory::draw(sf::RenderWindow &window) {
    for (auto itr = enemies.begin(); itr != enemies.end(); ++itr) {
        (*itr)->draw(window);
    }
}
