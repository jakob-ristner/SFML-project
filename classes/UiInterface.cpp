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
    background.setFillColor(sf::Color(31, 31, 31));

    foreground.setSize(sf::Vector2f(0, 15));
    foreground.setOrigin(sf::Vector2f(background.getSize().x / 2,
                                      background.getSize().y / 2));
    foreground.setPosition(sf::Vector2f(Settings::WINDOW_WIDTH / 2,
                                        600));
    foreground.setFillColor(sf::Color(0, 200, 255));
    position = background.getPosition();
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
    position += distance;
}

void CastBar::setPosition(sf::Vector2f pos) {
    move(pos - position);
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

PlayerStatBar::PlayerStatBar() {
    background.setSize(sf::Vector2f(200.0f, 15.0f));
    background.setPosition(sf::Vector2f((Settings::WINDOW_WIDTH - background.getSize().x) / 2, Settings::WINDOW_HEIGHT - 44.0f));
    background.setFillColor(sf::Color(31, 31, 31));
    background.setOutlineColor(sf::Color(51, 51, 51));
    background.setOutlineThickness(2);

    foreground.setSize(sf::Vector2f(200.0f, 15.0f));
    foreground.setPosition(sf::Vector2f((Settings::WINDOW_WIDTH - foreground.getSize().x) / 2, Settings::WINDOW_HEIGHT - 44.0f));
    foreground.setFillColor(sf::Color(200, 0, 0));

    statText.setFillColor(sf::Color::White);
    statText.setFontSize(14);
    position = background.getPosition();
}

PlayerStatBar::~PlayerStatBar() {

}

void PlayerStatBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background);
    target.draw(foreground);
    target.draw(statText);
}

void PlayerStatBar::move(sf::Vector2f distance) {
    background.move(distance);
    foreground.move(distance);
    statText.move(distance);
    position = background.getPosition();
}

void PlayerStatBar::setPosition(sf::Vector2f pos) {
    move(pos - position);
}

void PlayerStatBar::update(float newStat) {
    stat = std::max(newStat, 0.0f);
    foreground.setSize(sf::Vector2f((stat / maxStat) * background.getSize().x, foreground.getSize().y));
    statText.setString(std::to_string(int(stat)) + "/" + std::to_string(int(maxStat)));
    statText.setPosition(sf::Vector2f(0, -3) + position + (background.getSize() - statText.getDims()) / 2.0f);
}

void PlayerStatBar::setMaxStat(float newStat) {
    maxStat = newStat;
    update(maxStat);
}

PlayerHpBar::PlayerHpBar() {

}

PlayerHpBar::~PlayerHpBar() {

}

PlayerManaBar::PlayerManaBar() {
    foreground.setFillColor(sf::Color(0, 0, 220));
}

PlayerManaBar::~PlayerManaBar() {

}

PlayerStaminaBar::PlayerStaminaBar() {
    foreground.setFillColor(sf::Color(0, 180, 0));
}

PlayerStaminaBar::~PlayerStaminaBar() {

}

PlayerLevelIcon::PlayerLevelIcon() {
    level = 0;
    bgTexture.create(172, 172, false);
    bgTexture.setSmooth(true);

    background.setRadius(80);
    background.setFillColor(sf::Color(100, 100, 100));
    background.setOutlineThickness(6);
    background.setOutlineColor(sf::Color(51, 51, 51));
    background.setPosition(sf::Vector2f(background.getOutlineThickness(), background.getOutlineThickness()));

    bgTexture.draw(background);
    bgTexture.display();
    bgSprite.setTexture(bgTexture.getTexture());
    bgSprite.setScale(sf::Vector2f(0.5f, 0.5f));
        
    levelText.setString(std::to_string(level));
    levelText.setFontSize(40);
    levelText.setPosition(sf::Vector2f(-1 + 2, -14 + 5) + position + (sf::Vector2f(background.getRadius(), background.getRadius()) - levelText.getDims()) / 2.0f);
    levelText.setFillColor(sf::Color::White);
    setPosition(sf::Vector2f(10, (float) Settings::WINDOW_HEIGHT - background.getRadius() - 10));

}

PlayerLevelIcon::~PlayerLevelIcon() {

}

void PlayerLevelIcon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(bgSprite);
    target.draw(levelText);
}

void PlayerLevelIcon::move(sf::Vector2f distance) {
    bgSprite.move(distance);
    levelText.move(distance);
    position += distance;
}

void PlayerLevelIcon::setPosition(sf::Vector2f pos) {
    move(pos - position);
}

void PlayerLevelIcon::update(float newLevel) {
    level = newLevel;
    levelText.setString(std::to_string(level));
}
