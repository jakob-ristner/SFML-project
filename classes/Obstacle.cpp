#include <SFML/Graphics.hpp>
#include "../headers/Obstacle.h"


Obstacle::Obstacle(sf::Vector2f pos, sf::Vector2f size) {
    body = sf::RectangleShape(size);
    body.setOrigin(sf::Vector2f(16.0f, 16.0f));
    body.setPosition(pos);
}

Obstacle::~Obstacle() {

}

Collider Obstacle::getCollider() {
    return Collider(body, sf::Vector2f(0.0f, 0.0f));
}

sf::Vector2f Obstacle::getPos() {
    return body.getPosition();
}

CellDoor::CellDoor(sf::Vector2f pos, sf::Vector2f size, std::string link, sf::Vector2f linkPos) {
    body = sf::RectangleShape(size);
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(pos);
    this->linkPos = linkPos;
    this->link = link;
}

CellDoor::~CellDoor () {

}

Collider CellDoor::getCollider() {
    return Collider(body, sf::Vector2f(0.0f, 0.0f));
}

std::string CellDoor::getLinkedMap() {
    return link;
}

sf::Vector2f CellDoor::getLinkedPos() {
    return linkPos;
}

AnimatedTerrain::AnimatedTerrain(Animation &anim): anim(anim) {
    this->anim = anim;
    sf::Texture &text = *(anim.getSheet());
    setTexture(text);
    setTextureRect(anim.getTextureRect());
    setOrigin(anim.getOrigin());
}

AnimatedTerrain::~AnimatedTerrain() {

}

void AnimatedTerrain::update() {
    setTextureRect(anim.getTextureRect());
    setOrigin(anim.getOrigin());
}

void AnimatedTerrain::draw(sf::RenderWindow &window) {
    window.draw(*this);
}
