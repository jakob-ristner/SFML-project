
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/Player.h"
#include "../headers/Settings.h"

Player::Player(sf::RectangleShape body) {
    pos = sf::Vector2f(0, 0);
    speed = 4;
    settings = Settings();
    playeracc = 2;
    fric = 1.2;
    this->body = body;
    this->body.setFillColor(sf::Color::Green);
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
    acc = sf::Vector2f(0, 0);
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
    acc.x += vel.x / fric;
    acc.y += vel.y / fric;

    vel.x = acc.x;
    vel.y = acc.y;
    //std::cout << acc.x << std::endl;

    pos += vel * (dt / settings.TIMESCALE);

    body.setPosition(pos);
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(body);
}