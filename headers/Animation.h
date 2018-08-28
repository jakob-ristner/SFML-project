#pragma once
#include <SFML/Graphics.hpp>

class Animation {
public:
    // Dont use, only for placeholder variables
    Animation();
    // Use this
    Animation(sf::Texture &spriteSheet, sf::Vector2f size, 
              float animLength, float currTime, float frames, int currFrame);
    ~Animation();

    void update(float dt);
    sf::Texture *getSheet();
    sf::IntRect getTextureRect();
    sf::Vector2f getOrigin();

private:
    sf::Texture *spriteSheet;
    sf::Vector2f size;

    float animLength;
    float currTime;
    float frames;
    int currFrame;
};

class TerrainAnimation: public sf::Sprite {
public:
    TerrainAnimation(Animation &anim);
    ~TerrainAnimation();

    void update(float dt);
    void draw(sf::RenderWindow &window);

private:
    Animation &anim;
}
