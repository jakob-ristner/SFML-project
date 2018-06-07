#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


// Class that serves as a layer to draw other drawables
// on. Then draws to screen with window.draw(this)
// (the same as Sprites or any other sf:: drawable)
// Args:
// drawables - Vector with all initial drawables
class RenderLayer: public sf::Drawable {
public:
    RenderLayer();
    RenderLayer(std::vector<sf::Drawable *> drawables);
    ~RenderLayer();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void add(sf::Drawable *drawable);

protected:
    typedef std::vector<sf::Drawable *> DrawableList;

private:
    DrawableList drawables;
};

