#pragma once
#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation(sf::Texture &spriteSheet, sf::Vector2f size, 
              float animLength, float time, float frames);
    ~Animation();

    void update(float dt);
    sf::Texture *getFrame();

private:
    sf::Texture &spriteSheet;

    float animLength;
    float time;
    float frames;
}
