#include <SFML/Graphics.hpp>
#include <iostream>

#include "../headers/UiInterface.h"
#include "../headers/Settings.h"


UiElement::UiElement() {
    position = sf::Vector2f(0, 0);
    mainFont.loadFromFile("font.ttf");
}

UiElement::~UiElement() {

}

CastBar::CastBar() {
    progress = 0;
    casting = false;


    background.setSize(sf::Vector2f(204, 19));
    background.setOrigin(sf::Vector2f(background.getSize().x / 2,
                                      background.getSize().y / 2));
    background.setPosition(sf::Vector2f(Settings::WINDOW_WIDTH / 2 - 2,
                                        598));
    background.setFillColor(sf::Color(51, 51, 51));

    foreground.setSize(sf::Vector2f(0, 15));
    foreground.setOrigin(sf::Vector2f(background.getSize().x / 2,
                                      background.getSize().y / 2));
    foreground.setPosition(sf::Vector2f(Settings::WINDOW_WIDTH / 2,
                                        600));
    foreground.setFillColor(sf::Color(0, 200, 255));
}

CastBar::~CastBar() {

}

void CastBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (casting) {
        target.draw(background);
        target.draw(foreground);
    }
}

void CastBar::move(sf::Vector2f distance) {
    background.move(distance);
    foreground.move(distance);
}

void CastBar::setPosition(sf::Vector2f pos) {
    position = pos;
}

// Updates the casting bars current progress and therefore size
// of the foreground.
// Args:
// newProgress - Float representing how many seconds the spell has been
//               casted for
// castTime    - Float representing the total casting time of a spell
// isCasting   - Boolean coming from player, tells the bar if the spell
//               has been canceled or not
void CastBar::update(float newProgress, float castTime, bool isCasting) {
    progress = newProgress;
    casting = isCasting;
    this->castTime = castTime;

    foreground.setSize(sf::Vector2f((progress / castTime) * 200, 15));
}

UiText::UiText() {
    text = sf::Text();
}

UiText::UiText(sf::Text text) {
    this->text = text;
}

UiText::~UiText() {

}

void UiText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(text);
}

void UiText::move(sf::Vector2f distance) {
    text.move(distance);
}

void UiText::setPosition(sf::Vector2f pos) {
    text.setPosition(pos);
}

void UiText::setString(std::string str) {
    text.setString(str);
}

void UiText::setFillColor(sf::Color color) {
    text.setFillColor(color);
}

void UiText::setFont(sf::Font font) {
    text.setFont(font);
}

void UiText::setFontSize(unsigned int size) {
    text.setCharacterSize(size);
}

SpellBarIcon::SpellBarIcon() {
    background.setPosition(sf::Vector2f(0, 0));
    background.setSize(sf::Vector2f(30, 30));
    background.setFillColor(sf::Color(51, 51, 51));

    slotIdText.setString("1");
    slotIdText.setFont(mainFont);
    slotIdText.setFontSize(28);
    slotIdText.setFillColor(sf::Color::White);
    slotIdText.setPosition(sf::Vector2f(2, 2));

    selected = false;
    slotId = 1;
}

SpellBarIcon::SpellBarIcon(int id) {
    SpellBarIcon();
    slotIdText.setString(std::to_string(id));
    slotId = id;
}

SpellBarIcon::~SpellBarIcon() {

}

void SpellBarIcon::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(background);
    target.draw(slotIdText);
}

void SpellBarIcon::move(sf::Vector2f distance) {
    background.move(distance);
    slotIdText.move(distance);
}

void SpellBarIcon::setPosition(sf::Vector2f pos) {
    background.setPosition(pos);
    // Maybe change the addition
    slotIdText.setPosition(pos + sf::Vector2f(2, 2)); 
    position = pos;
}
