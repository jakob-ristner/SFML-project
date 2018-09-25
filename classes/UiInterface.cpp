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

void UiElement::toggleDebugMode() {
    debugMode = !debugMode;
}

CastBar::CastBar() {
    progress = 0;
    casting = false;


    background.setSize(sf::Vector2f(200, 15));
    background.setOrigin(sf::Vector2f(background.getSize().x / 2,
                                      background.getSize().y / 2));
    background.setPosition(sf::Vector2f(Settings::WINDOW_WIDTH / 2,
                                        600));
    background.setFillColor(sf::Color(31, 31, 31));
    background.setOutlineColor(sf::Color(51, 51, 51));
    background.setOutlineThickness(2);

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
    //std::cout << text.getString().toAnsiString() << std::endl;
    //std::cout << text.getPosition().x << " " << text.getPosition().y << std::endl;
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

void SpellBarIcon::setFont(sf::Font &font) {
    slotIdText.setFont(font);
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

sf::Vector2f SpellBarIcon::getSize() {
    return background.getSize();
}

void SpellBarIcon::setSelected(bool isSelected) {
    selected = isSelected;
    if (selected) {
        background.setOutlineThickness(3);
    } else {
        background.setOutlineThickness(0);
    }
}

UiText* SpellBarIcon::getText() {
    return &slotIdText;
}

SpellBar::SpellBar() {
    selected = 0;
    size = sf::Vector2f(800, 30);
}

SpellBar::SpellBar(int amount) {
    size = sf::Vector2f(600, 30); // Räkna med sista spejset
    std::vector<SpellBarIcon> tmp;
    for (int i = 1; i <= amount; i++) {
        tmp.push_back(SpellBarIcon(i));
    }
    setSpellIcons(tmp);
    for (int i = 0; i < amount; i++) {
        icons[i].setFont(mainFont);
        (*(icons[i].getText())).setPosition(icons[i].getPosition());
        (*(icons[i].getText())).move(sf::Vector2f(8, -3));
    }
    changeSelection(1);
    background.setPosition(sf::Vector2f(0, 0));
    background.setSize(size);
    background.setFillColor(sf::Color::Red);
    debugMode = false;
}

SpellBar::~SpellBar() {

}

void SpellBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (debugMode) {
        target.draw(background);
    }
    for (int i = 0; i < icons.size(); i++) {
        target.draw(icons[i]);
    }
}

void SpellBar::move(sf::Vector2f distance) {
    position += distance;
    background.move(distance);
    for (int i = 0; i < icons.size(); i++) {
        icons[i].move(distance);
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
       icons[i].setSelected(false);
    }
    icons[selected].setSelected(true);

}

void SpellBar::setSpellIcons(std::vector<SpellBarIcon> newIcons) {
    icons = newIcons;
    for (int i = 0; i < icons.size(); i++) {
        icons[i].setPosition(position + sf::Vector2f((size.x - icons[0].getSize().x) / (icons.size() - 1)* i, 0));
    }
}

void SpellBar::update() {

}

sf::Vector2f SpellBar::getSize() {
    return size;
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
    levelText.setPosition(sf::Vector2f(-1 + 2, -14 + 5) + position + (sf::Vector2f(background.getRadius(), background.getRadius()) - levelText.getDims()) / 2.0f);
}

UiGrid::UiGrid() {
    text.create(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT, false);
        visible = false;
    xAmount = 8;
    yAmount = 8;
    lineColor = sf::Color::Red;
    render();
}

UiGrid::~UiGrid() {

}

void UiGrid::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (visible) {
        target.draw(sprite);
    }
}

void UiGrid::move(sf::Vector2f distance) {
    sprite.move(distance);
    position += distance;
}

void UiGrid::setPosition(sf::Vector2f pos) {
    move(pos - position);
}

void UiGrid::setVisibility(bool newVisible) {
    visible = newVisible;
}

void UiGrid::setXLines(int amount) {
    xAmount = amount;
    render();
}

void UiGrid::setYLines(int amount) {
    yAmount = amount;
    render();
}

void UiGrid::render() {
    sf::RectangleShape line;
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(Settings::WINDOW_WIDTH, 1));
    text.clear(sf::Color::Transparent);
    for (float y = 0; y < yAmount; y++) {
        line.setPosition(sf::Vector2f(0, y * Settings::WINDOW_HEIGHT / yAmount));
        text.draw(line);
    }
    line.setSize(sf::Vector2f(1, Settings::WINDOW_HEIGHT));
    for (float x = 0; x < xAmount; x++) {
        line.setPosition(sf::Vector2f(x * Settings::WINDOW_WIDTH / xAmount, 0));
        text.draw(line);
    }

    text.display();
    sprite.setTexture(text.getTexture());
}

void UiGrid::setColor(sf::Color color) {
    lineColor = color;
    render();
}

bool UiGrid::isVisible() {
    return visible;
}

StatusMessage::StatusMessage() {

}

StatusMessage::~StatusMessage() {
    
}

void StatusMessage::update(float dt) {
    
}

void StatusMessage::draw(sf::RenderTarget &target, sf::RenderStates states) {

}

std::string StatusMessage::getMessage() {

}

PauseMenu::PauseMenu() {
     title.setFontSize(60);
     title.setString("Paused");
     title.setFillColor(sf::Color::White);

     titleSeparator.setSize(sf::Vector2f(400, 3));
     titleSeparator.setFillColor(sf::Color::White);

     menuOptions.resize(3);
     for (int i = 0; i < nOptions; i++) {
        menuOptions[i] = UiText();
        menuOptions[i].setFont(menuOptions[i].mainFont);
        menuOptions[i].setFontSize(50);
        menuOptions[i].setFillColor(sf::Color::White);
     }
     menuOptions[0].setString("Inventory");
     menuOptions[1].setString("Settings");
     menuOptions[2].setString("Exit");
}

PauseMenu::~PauseMenu() {

}

void PauseMenu::open(sf::RenderWindow &window, sf::Clock &clock, sf::View &viewport) {
    sf::Texture bgTexture;
    bgTexture.create(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT);
    bgTexture.update(window);

    //bgTexture.loadFromImage(window.capture());

    sf::Vector2f viewCenter = viewport.getCenter();
    sf::Vector2f topLeftPos;
    topLeftPos.x = viewCenter.x - Settings::WINDOW_WIDTH / 2;
    topLeftPos.y = viewCenter.y - Settings::WINDOW_HEIGHT / 2;
    std::cout << viewCenter.x << " " << viewCenter.y << std::endl;
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(topLeftPos);

    bgRibbon.setPosition(sf::Vector2f(topLeftPos.x + 20, topLeftPos.y));
    bgRibbon.setSize(sf::Vector2f(400, Settings::WINDOW_HEIGHT * 2));
    bgRibbon.setFillColor(sf::Color(0, 0, 0, 120));
    bgRibbon.setRotation(-45);

    bgDim.setSize(sf::Vector2f(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT));
    bgDim.setPosition(topLeftPos);
    bgDim.setFillColor(sf::Color(0, 0, 0, 100));

    title.setPosition(sf::Vector2f(topLeftPos.x + 260, topLeftPos.y + 10));
    titleSeparator.setPosition(sf::Vector2f(topLeftPos.x + 170, topLeftPos.y + 80));

    for (int i = 0; i < nOptions; i++) {
        sf::Vector2f dims = menuOptions[i].getDims();
        menuOptions[i].setPosition(sf::Vector2f(
                    topLeftPos.x + 150 + i * 100 + (288 - dims.x / 2), 
                    topLeftPos.y + 120 + i * 100));
    }

    bool isOpen = true;
    sf::Time frameDelta;
    float dt;
    sf::Event event;
    while (isOpen) {
        frameDelta = clock.restart();
        dt = frameDelta.asMilliseconds();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isOpen = false;
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Key::W:
                        break;
                    case sf::Keyboard::Key::S:
                        break;
                    case sf::Keyboard::Key::Escape:
                        isOpen = false;
                }
            }
        }
        // Drawing
        window.clear(sf::Color(51, 51, 51));
        window.draw(bgSprite);
        window.draw(bgDim);
        window.draw(bgRibbon);
        window.draw(title);
        window.draw(titleSeparator);
        for (int i = 0; i < nOptions; i++) {
            window.draw(menuOptions[i]);
        }
        window.display();
    }
}

void PauseMenu::update(float dt) {

}

void PauseMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {

}

void PauseMenu::move(sf::Vector2f distance) {

}

void PauseMenu::setPosition(sf::Vector2f pos) {

}
