
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/Player.h"
#include "../headers/Settings.h"

Player::Player(sf::RectangleShape body) {
    pos = sf::Vector2f(0, 0);
    speed = 4;
    this->body = body;
    this->body.setFillColor(sf::Color::Blue);
    settings = Settings();
}

Player::~Player() {

}

sf::Vector2f Player::getPos() {
    return pos;
}

void Player::setPos(sf::Vector2f newPos) {
    pos = newPos;
}

void Player::update(float dt) {
    vel = sf::Vector2f(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        vel.y = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        vel.y = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        vel.x = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        vel.x = speed;
    }
    pos += vel * (dt / settings.TIMESCALE);
    body.setPosition(pos);
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(body);
}