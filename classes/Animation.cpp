#include <SFML/Graphics.hpp>
#include <iostream>

#include "../headers/Animation.h"

Animation::Animation(sf::Texture &spriteSheet, sf::Vector2f size,
        float animLength, float currTime, float frames, int currFrame) {
    this->spriteSheet = &spriteSheet;
    this->animLength = animLength;
    this->currTime = currTime;
    this->frames = frames;
    this->currFrame = currFrame;
}

Animation::~Animation() {

}

void Animation::update(float dt) {
    currTime += dt;
    if (currTime > animLength / frames) {
        currFrame++;
        currTime -= animLength / frames;
        std::cout << "Reset: " << currFrame << std::endl;
    }
}

sf::Texture *Animation::getFrame() {
    return spriteSheet;
}
