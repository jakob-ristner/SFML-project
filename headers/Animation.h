#pragma once
#include <SFML/Graphics.hpp>

// Object that holds sprite sheet and keeps track of which frame is active one. 
// Needs to be updated with delta time between frames.
// Args:
// spriteSheet - Reference to the spritesheet texture
// size        - size of one tile in the sheet
// animLength  - total time 
// currTime    - start time offset, most often will be 0
// frames      - how many frames there are in the entire animation
// currFrame   - initial frame offset
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
    static int animation_count;

private:
    sf::Texture *spriteSheet;
    sf::Vector2f size;

    float animLength;
    float currTime;
    float frames;
    int currFrame;
};

// Wrapper for animations on static terrain scenery
// Args:
// anim - pointer to the terrain animation object
class TerrainAnimation: public sf::Sprite {
public:
    TerrainAnimation(Animation *anim);
    ~TerrainAnimation();

    void update();
    void draw(sf::RenderWindow &window);

private:
    Animation *anim;
};
