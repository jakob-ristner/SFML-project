#include <SFML/Graphics.hpp>
#include <iostream>

#include "../headers/Animation.h"

int Animation::animation_count = 0;

Animation::Animation() {

}

Animation::Animation(sf::Texture &spriteSheet, sf::Vector2f size,
        float animLength, float currTime, float frames, int currFrame) {
    this->spriteSheet = &spriteSheet;
    spriteSheet.setRepeated(true);
    this->size = size;
    this->animLength = animLength;
    this->currTime = currTime;
    this->frames = frames;
    this->currFrame = currFrame;
    animation_count++;
    std::cout << "Anim count " << animation_count << std::endl;
}

Animation::~Animation() {

}

void Animation::update(float dt) {
    currTime += dt;
    //std::cout << "Current time: "<< currTime << std::endl;
    //std::cout << currFrame << std::endl;
    if (currTime >= animLength / frames) {
        int i = 0;
        while (currTime >= animLength / frames) {
            std::cout << "FLAFLAFLAFLAFLAFL" << std::endl;
            std::cout << currFrame << std::endl;
            currFrame++;
            std::cout << currFrame << std::endl;
            currTime -= animLength / frames;
            i++;
        }
    }
}

sf::Texture *Animation::getSheet() {
    return spriteSheet;
}

sf::IntRect Animation::getTextureRect() {
    //std::cout << "getTextureRect " << currFrame << std::endl;
    return sf::IntRect(currFrame * size.x, 0, size.x, size.y);
}

sf::Vector2f Animation::getOrigin() {
    sf::IntRect r = getTextureRect();
    return sf::Vector2f(r.left + (r.width / 2.0f), r.top + (r.height / 2.0f));
}

TerrainAnimation::TerrainAnimation(Animation *anim) {
    this->anim = anim;
    setTexture(*((*anim).getSheet()));
    std::cout << "isRepeated" << getTexture()->isRepeated() << std::endl;
    setOrigin((*anim).getOrigin());
    setTextureRect((*anim).getTextureRect());
}

TerrainAnimation::~TerrainAnimation() {

}

void TerrainAnimation::update() {
    sf::IntRect test = (*anim).getTextureRect();
    //std::cout << test.left << " " << test.top << " " << test.width << " " << test.height << std::endl;
    setTextureRect((*anim).getTextureRect());
    //std::cout << getPosition().x << " " << getPosition().y << std::endl;
}

void TerrainAnimation::draw(sf::RenderWindow &window) {
    window.draw(*this);
}
