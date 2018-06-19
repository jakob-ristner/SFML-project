#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>

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
    setFont(mainFont);
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

void UiText::setFont(sf::Font &font) {
    text.setFont(font);
}

void UiText::setFontSize(unsigned int size) {
    text.setCharacterSize(size);
}

sf::Vector2f UiText::getDims() {
    sf::FloatRect dims = text.getLocalBounds();
    return sf::Vector2f(dims.width, dims.height);
}

SpellBarIcon::SpellBarIcon() {
    background.setPosition(sf::Vector2f(0, 0));
    background.setSize(sf::Vector2f(30, 30));
    background.setFillColor(sf::Color(51, 51, 51));
    background.setOutlineColor(sf::Color::Green);

    slotIdText.setFont(mainFont);
    slotIdText.setString("1");
    slotIdText.setFontSize(28);
    slotIdText.setFillColor(sf::Color::White);
    slotIdText.setPosition(sf::Vector2f(0, -10) + (background.getSize() - slotIdText.getDims()) / 2.0f); 

    selected = false;
    slotId = 1;
}

SpellBarIcon::SpellBarIcon(int id): SpellBarIcon() {
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
    position += distance;
}

void SpellBarIcon::setPosition(sf::Vector2f pos) {
    background.setPosition(pos);
    // Maybe change the addition
    slotIdText.setPosition(sf::Vector2f(0, -10) + pos + (background.getSize() - slotIdText.getDims()) / 2.0f); 
    position = pos;
}

sf::Vector2f SpellBarIcon::getPosition() {
    return background.getPosition();
}

void SpellBarIcon::setSelected(bool isSelected) {
    selected = isSelected;
    if (selected) {
        background.setOutlineThickness(3);
    } else {
        background.setOutlineThickness(0);
    }
}

SpellBar::SpellBar() {
    selected = 0;
    size = sf::Vector2f(800, 30);
}

SpellBar::~SpellBar() {

}

void SpellBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (int i = 0; i < icons.size(); i++) {
        target.draw(*icons[i]);
    }
}

void SpellBar::move(sf::Vector2f distance) {
    position += distance;
    for (int i = 0; i < icons.size(); i++) {
        (*icons[i]).move(distance);
    }
}

void SpellBar::setPosition(sf::Vector2f pos) {
    move(pos - position);
}

void SpellBar::setSize(sf::Vector2f size) {
    this->size = size;
}

void SpellBar::changeSelection(unsigned short int id) {
    selected = id - 1;
    for (int i = 0; i < icons.size(); i++) {
       (*icons[i]).setSelected(false);
    }
    (*icons[selected]).setSelected(true);

}

void SpellBar::setSpellIcons(std::vector<SpellBarIcon *> newIcons) {
    icons = newIcons;
    for (int i = 0; i < icons.size(); i++) {
        (*icons[i]).setPosition(position + sf::Vector2f((size.x / icons.size()) * i, 0));
    }
}

void SpellBar::update() {

}

PlayerHpBar::PlayerHpBar() {
    redShape.setSize(sf::Vector2f(200.0f, 15.0f));
    redShape.setPosition(sf::Vector2f((Settings::WINDOW_WIDTH - redShape.getSize().x) / 2, Settings::WINDOW_HEIGHT - 44.0f));
    redShape.setFillColor(sf::Color::Red);
    redShape.setOutlineColor(sf::Color(51, 51, 51));
    redShape.setOutlineThickness(2);

    greenShape.setSize(sf::Vector2f(200.0f, 15.0f));
    greenShape.setPosition(sf::Vector2f((Settings::WINDOW_WIDTH - greenShape.getSize().x) / 2, Settings::WINDOW_HEIGHT - 44.0f));
    greenShape.setFillColor(sf::Color::Green);

    hpText.setFillColor(sf::Color::Black);
    hpText.setFontSize(14);
    position = redShape.getPosition();
}

PlayerHpBar::~PlayerHpBar() {

}

void PlayerHpBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(redShape);
    target.draw(greenShape);
    target.draw(hpText);
}

void PlayerHpBar::move(sf::Vector2f distance) {
    redShape.move(distance);
    greenShape.move(distance);
    hpText.move(distance);
    position = redShape.getPosition();
}

void PlayerHpBar::setPosition(sf::Vector2f pos) {
    move(pos - position);
    position = redShape.getPosition();
}

void PlayerHpBar::update(float newHp) {
    hp = std::max(newHp, 0.0f);
    greenShape.setSize(sf::Vector2f((hp / maxHp) * redShape.getSize().x, greenShape.getSize().y));
    hpText.setString(std::to_string(int(hp)) + "/" + std::to_string(int(maxHp)));
    hpText.setPosition(sf::Vector2f(0, -3) + position + (redShape.getSize() - hpText.getDims()) / 2.0f);
}

void PlayerHpBar::setMaxHp(float newMaxHp) {
    maxHp = newMaxHp;
    update(maxHp);
}
