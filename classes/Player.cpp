
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "../headers/Player.h"
#include "../headers/Settings.h"
#include "../headers/Utils.h"
#include "../headers/Collider.h"

Player::Player(sf::RectangleShape body) {
    pos = sf::Vector2f(0, 0);
    speed = 1;
    settings = Settings();
    std::vector<sf::Sprite> projectiles = std::vector<sf::Sprite> {};
    spellInventory = std::vector<Spell *> {};
    playeracc = 0.5;
    fric = 1.2;
    this->body = body;
    this->body.setFillColor(sf::Color::Green);
    this->body.setOrigin(sf::Vector2f(body.getSize().x / 2, body.getSize().y / 2));
}

Player::Player() {

}

Player::~Player() {

}

void Player::castSpell(int index) {
    Spell test = *spellInventory[index];
    test.use();
}

void Player::addSpell(Spell *spell) {
    spellInventory.push_back(spell);
}

void Player::addProjectile(Projectile projectile) {
    projectiles.push_back(projectile);
 
}

Spell *Player::getSpell(int index) {
    return spellInventory[index];
}

sf::Vector2f Player::getPos() {
    return body.getPosition();
}

std::vector<Projectile> &Player::getProjectiles() {
    return projectiles;
}

void Player::setPos(sf::Vector2f newPos) {
    pos = newPos;
    body.setPosition(newPos);
}

void Player::update(float dt) {
    acc = sf::Vector2f(0, 0);
    pos = body.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        acc.y = -playeracc;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        acc.y = playeracc;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        acc.x = -playeracc;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        acc.x = playeracc;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        body.rotate(-1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        body.rotate(1);
    }

    if(!(acc.x == 0.0f || acc.y == 0.0f)) {
        acc = normalizedVec(acc) * playeracc;
    }

    acc += vel / fric;

    vel = acc;
    //body.rotate(1);
    //std::cout << acc.x << std::endl;

    pos += vel * (dt / settings.TIMESCALE);

    body.setPosition(pos);
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(body);
}

Collider Player::getCollider() {
    return Collider(body, vel);
}

void Player::onCollision(sf::Vector2f direction) {
    if (direction.x != 0.0f) {
        vel.x = 0.0f;
        acc.x = 0.0f;
    } else if (direction.y != 0.0f) {
        vel.y = 0.0f;
        acc.y = 0.0f;
    }


    sf::Vector2f oldPos = body.getPosition();
    //body.setPosition(std::round(oldPos.x), std::round(oldPos.y));
    body.setPosition(oldPos.x, oldPos.y);
}

void Player::setMouseAngle(float angle) {
    mouseAngle = angle;
}

float Player::getMouseAngle() {
    return mouseAngle;
}

float Player::getMouseAngleRad() {
    return mouseAngle * (M_PI / 180);
}