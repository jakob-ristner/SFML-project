// Layers for rendering
#include "../headers/RenderLayer.h"

RenderLayer::RenderLayer() {

}

RenderLayer::RenderLayer(std::vector<sf::Drawable *> drawables) {
    this->drawables = drawables;
}

RenderLayer::~RenderLayer() {

}

// function called by window.draw() -- No need to touch
void RenderLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (int i = 0; i < drawables.size(); i++) {
        target.draw(*drawables[i]);
    }
}

// Adds a drawable to the list of drawables
void RenderLayer::add(sf::Drawable *drawable) {
    drawables.push_back(drawable);
}

