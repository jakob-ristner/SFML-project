
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/Player.h"
#include "../headers/Settings.h"
#include "../headers/Utils.h"

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
    body.setOrigin(sf::Vector2f(16, 16));
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        body.rotate(-1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        body.rotate(1);
    }

    // if(!(acc.x == 0.0f || acc.y == 0.0f)) {
    //     std::cout << acc.x << "," << acc.y << std::endl;
    //     acc = normalizedVec(acc) * playeracc;
    // }

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