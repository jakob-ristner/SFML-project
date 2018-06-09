#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "./UiInterface.h"

// Class that serves as a layer to draw other drawables
// on. Then draws to screen with window.draw(this)
// (the same as Sprites or any other sf:: drawable)
// Args:
// drawables - Vector with all initial drawables
class RenderLayer: public sf::Drawable {
public:
    RenderLayer();
    RenderLayer(std::vector<UiElement *> elements);
    ~RenderLayer();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void add(UiElement *element);
    void setPosition(sf::Vector2f pos);

protected:
    typedef std::vector<UiElement *> ElementList;

private:
    ElementList elements;
    sf::Vector2f position;
};

