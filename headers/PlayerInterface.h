#pragma once
#include <SFML/Graphics.hpp>
#include "./Settings.h"


class CastBar: public sf::Drawable {
public:
    CastBar();
    ~CastBar();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void update(float newProgress, float castTime, bool isCasting);

private:
    sf::RectangleShape foreground;
    sf::RectangleShape background;

    float progress;
    float castTime;

    bool casting;
};
