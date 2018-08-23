#pragma once
#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation(sf::Texture &spriteSheet, sf::Vector2f size, 
              float animLength, float currTime, float frames, int currFrame);
    ~Animation();

    void update(float dt);
    sf::Texture *getFrame();

private:
    sf::Texture *spriteSheet;

    float animLength;
    float currTime;
    float frames;
    int currFrame;
};
