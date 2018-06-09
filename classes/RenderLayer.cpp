// Layers for rendering
#include "../headers/RenderLayer.h"

RenderLayer::RenderLayer() {

}

RenderLayer::RenderLayer(std::vector<UiElement *> elements) {
    this->elements = elements;
}

RenderLayer::~RenderLayer() {

}

// function called by window.draw() -- No need to touch
void RenderLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (int i = 0; i < elements.size(); i++) {
        target.draw(*elements[i]);
    }
}

// Adds a drawable to the list of drawables
void RenderLayer::add(UiElement *element) {
    elements.push_back(element);
}

void RenderLayer::setPosition(sf::Vector2f pos) {
    for (int i = 0; i < elements.size(); i++) {
        (*elements[i]).move(pos - position);
    }
    position = pos;
}
