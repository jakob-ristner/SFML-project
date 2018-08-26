#include <SFML/Graphics.hpp>
#include <iostream>

#include "../headers/Animation.h"

Animation::Animation() {

}

Animation::Animation(sf::Texture &spriteSheet, sf::Vector2f size,
        float animLength, float currTime, float frames, int currFrame) {
    this->spriteSheet = &spriteSheet;
    this->size = size;
    this->animLength = animLength;
    this->currTime = currTime;
    this->frames = frames;
    this->currFrame = currFrame;
}

Animation::~Animation() {

}

void Animation::update(float dt) {
    currTime += dt;
    if (currTime >= animLength / frames) {
        int i = 0;
        while (currTime >= animLength / frames) {
            currFrame++;
            currTime -= animLength / frames;
            i++;
        }
    }
}

sf::Texture *Animation::getSheet() {
    return spriteSheet;
}

sf::IntRect Animation::getTextureRect() {
    return sf::IntRect(currFrame * size.x, 0, size.x, size.y);
}
