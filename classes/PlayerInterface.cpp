#include <SFML/Graphics.hpp>
#include "../headers/PlayerInterface.h"
#include "../headers/Settings.h"

CastBar::CastBar() {
    progress = 0;
    casting = false;


    background.setSize(sf::Vector2f(200, 15));
    background.setOrigin(sf::Vector2f(background.getSize().x / 2,
                                      background.getSize().y / 2));
    background.setPosition(sf::Vector2f(Settings::WINDOW_WIDTH / 2,
                                        600));
    background.setFillColor(sf::Color(51, 51, 51));

    foreground.setSize(sf::Vector2f(0, 15));
    foreground.setOrigin(sf::Vector2f(background.getSize().x / 2,
                                      background.getSize().y / 2));
    foreground.setPosition(sf::Vector2f(Settings::WINDOW_WIDTH / 2,
                                        600));
    foreground.setFillColor(sf::Color::Green);
}

CastBar::~CastBar() {

}

void CastBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (casting) {
        target.draw(background);
        target.draw(foreground);
    }
}

void CastBar::update(float newProgress, float castTime, bool isCasting) {
    progress = newProgress;
    casting = isCasting;
    this->castTime = castTime;

    foreground.setSize(sf::Vector2f((progress / castTime) * 200, 15));
}
