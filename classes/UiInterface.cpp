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
    cooldownPercent = 0;

    cooldownRect.setPosition(sf::Vector2f(0, 0));
    cooldownRect.setSize(sf::Vector2f(30 * cooldownPercent, 30));
    cooldownRect.setFillColor(sf::Color(0, 0, 0, 128));

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
void SpellBarIcon::update() {
    cooldownRect.setSize(sf::Vector2f(30 * cooldownPercent, 30));
}
 

void SpellBarIcon::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(background);
    target.draw(slotIdText);
    target.draw(cooldownRect);
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

void SpellBarIcon::setCooldown(float cooldownPercent) {
    this->cooldownPercent = cooldownPercent;
}

UiText* SpellBarIcon::getText() {
    return &slotIdText;
}

sf::RectangleShape* SpellBarIcon::getCooldownRect() {
    return &cooldownRect;
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
        (*(icons[i].getCooldownRect())).setPosition(icons[i].getPosition());
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
        (*(icons[i].getCooldownRect())).setPosition(icons[i].getPosition());
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
    for (int i = 0; i < icons.size(); i++) {
        icons[i].update();
    }
}

sf::Vector2f SpellBar::getSize() {
    return size;
}

std::vector<SpellBarIcon>* SpellBar::getIcons() {
    return &icons;
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
    update(stat);
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

    menuOptions.resize(nOptions);
    for (int i = 0; i < nOptions; i++) {
       menuOptions[i] = UiText();
       menuOptions[i].setFont(menuOptions[i].mainFont);
       menuOptions[i].setFontSize(50);
       menuOptions[i].setFillColor(sf::Color::White);
    }
    menuOptions[0].setString("Resume");
    menuOptions[1].setString("Inventory");
    menuOptions[2].setString("Settings");
    menuOptions[3].setString("Exit");
}

PauseMenu::~PauseMenu() {

}

// Move the selection indicator up or down. Also does out-of-bounds checks.
// Args:
// dir - amount of steps to take, -1 is up 1 is down
void PauseMenu::moveSelector(int dir) {
    selectedOption += dir;
    if (selectedOption < 0) {
        selectedOption = 0;
    } else if (selectedOption >= nOptions) {
        selectedOption = nOptions - 1;
    }
    selector.setPosition(sf::Vector2f(
                topLeftPos.x + 250 + selectedOption * 100,
                topLeftPos.y + 120 + selectedOption * 100));
    selector.setString(">                           <");
    blinkTimer = blinkDuration;
}

// Plays the slide animation from one pause menu position or opacity to another.
// This function is used for both opening and closing to avoid lots of 
// boilerplate code.
// Args:
// window       - reference to the main renderwindow
// clock        - reference to the main game clock
// viewport     - reference to the player view
// ribbonPos    - start position of the pause menu ribbon
// ribbonEndPos - end position of the ribbon
// startOpacity - starting opacity of the background
// finalOpacity - end opacity of the background
bool PauseMenu::playSlideAnim(sf::RenderWindow &window, sf::Clock &clock, 
        sf::View &viewport, int ribbonPos, int ribbonEndPos, 
        float startOpacity, float finalOpacity) {
    
    float currentOpacity = startOpacity;
    //bgTexture.create(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT);
    //bgTexture.update(window);
    
    viewCenter = viewport.getCenter();
    topLeftPos.x = viewCenter.x - Settings::WINDOW_WIDTH / 2;
    topLeftPos.y = viewCenter.y - Settings::WINDOW_HEIGHT / 2;
    
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(topLeftPos);
    
    bgRibbon.setPosition(sf::Vector2f(ribbonPos, topLeftPos.y));
    bgRibbon.setSize(sf::Vector2f(400, Settings::WINDOW_HEIGHT * 2));
    bgRibbon.setFillColor(sf::Color(0, 0, 0, 120));
    bgRibbon.setRotation(-45);
    
    bgDim.setSize(sf::Vector2f(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT));
    bgDim.setPosition(topLeftPos);
    bgDim.setFillColor(sf::Color(0, 0, 0, finalOpacity));
    
    title.setPosition(sf::Vector2f(ribbonPos + 240, topLeftPos.y + 10));
    titleSeparator.setPosition(sf::Vector2f(ribbonPos + 150, topLeftPos.y + 80));
    
    selector.setFontSize(50);
    selector.setString("");
    //selector.setPosition(sf::Vector2f(topLeftPos.x + 250 + selectedOption * 100, topLeftPos.y + 120 + selectedOption * 100));
    
    for (int i = 0; i < nOptions; i++) {
        sf::Vector2f dims = menuOptions[i].getDims();
        menuOptions[i].setPosition(sf::Vector2f(
                    ribbonPos + 130 + i * 100 + (288 - dims.x / 2), 
                    topLeftPos.y + 120 + i * 100));
    }
    
    bool isRunning = true;
    bool shouldClose = false;
    sf::Time frameDelta;
    float dt;
    float deltaX;
    float scrollSpeed = 5;
    float duration = (ribbonEndPos - ribbonPos) / scrollSpeed;
    float timeLeft = duration;
    sf::Event event;
    while (isRunning) {
        frameDelta = clock.restart();
        dt = frameDelta.asMicroseconds() / 1000;
        while (window.pollEvent(event)) {
            switch (event.type){
                case sf::Event::Closed:
                    shouldClose = true;
                    isRunning = false;
                    break;
            }
        }
        timeLeft -= dt;
        if (timeLeft < 0) {
            isRunning = false;
        }
        deltaX = std::min(scrollSpeed * dt, (float)(ribbonEndPos - ribbonPos));
        bgRibbon.move(sf::Vector2f(deltaX, 0));
        ribbonPos += deltaX;
        
        title.setPosition(sf::Vector2f(ribbonPos + 240, topLeftPos.y + 10));
        titleSeparator.setPosition(sf::Vector2f(ribbonPos + 150, topLeftPos.y + 80));
        for (int i = 0; i < nOptions; i++) {
            sf::Vector2f dims = menuOptions[i].getDims();
            menuOptions[i].setPosition(sf::Vector2f(
                        ribbonPos + 130 + i * 100 + (288 - dims.x / 2), 
                        topLeftPos.y + 120 + i * 100));
        }
        
        if (finalOpacity - startOpacity > 0) {
            currentOpacity += std::min((finalOpacity / duration) * dt, 
                    (float)(finalOpacity - currentOpacity));
        } else {
            currentOpacity  -= std::min((startOpacity / duration) * dt,
                    (float)(currentOpacity - finalOpacity));
        }
        bgDim.setFillColor(sf::Color(0, 0, 0, currentOpacity));

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
    return shouldClose;
}

// Calls slide animation as it's supposed to look when opening the pause menu
// Args:
// window       - reference to the main renderwindow
// clock        - reference to the main game clock
// viewport     - reference to the player view
bool PauseMenu::playStartAnim(sf::RenderWindow &window, sf::Clock &clock, 
        sf::View &viewport) {
    return playSlideAnim(window, clock, viewport, topLeftPos.x - 800, 
                         topLeftPos.x + 20, 0, 80);
}

// Calls slide animation as it's supposed to look when closing the pause menu
// Args:
// window       - reference to the main renderwindow
// clock        - reference to the main game clock
// viewport     - reference to the player view
bool PauseMenu::playCloseAnim(sf::RenderWindow &window, sf::Clock &clock, 
        sf::View &viewport) {
    return playSlideAnim(window, clock, viewport, topLeftPos.x + 20, 
                         topLeftPos.x + Settings::WINDOW_WIDTH, 80, 0);
}

// Opens the pause menu. Handles drawing, updating, window and keyboard events.
// Also plays opening and closing animations.
// Args:
// window       - reference to the main renderwindow
// clock        - reference to the main game clock
// viewport     - reference to the player view
bool PauseMenu::open(sf::RenderWindow &window, sf::Clock &clock, sf::View &viewport) {
    // Will be returned to tell main wheter a sf::Event::Closed has been sent
    bool shouldClose = false;
    // Gets current screen from the window and saves it for drawing every
    // frame. This saves a lot of processing power by not having to draw
    // every entity several times.
    bgTexture.create(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT);
    bgTexture.update(window);


    // Find offset of menu in worldspace through viewport center,
    // This is done because the player is not always in the center
    // of the screen and we already have a reference of the window.
    viewCenter = viewport.getCenter();
    topLeftPos.x = viewCenter.x - Settings::WINDOW_WIDTH / 2;
    topLeftPos.y = viewCenter.y - Settings::WINDOW_HEIGHT / 2;

    // Play start animation and store wether the window should be closed or not
    shouldClose = playStartAnim(window, clock, viewport);
    //std::cout << viewCenter.x << " " << viewCenter.y << std::endl;
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(topLeftPos);

    bgRibbon.setPosition(sf::Vector2f(topLeftPos.x + 20, topLeftPos.y));
    bgRibbon.setSize(sf::Vector2f(400, Settings::WINDOW_HEIGHT * 2));
    bgRibbon.setFillColor(sf::Color(0, 0, 0, 120));
    bgRibbon.setRotation(-45);

    bgDim.setSize(sf::Vector2f(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT));
    bgDim.setPosition(topLeftPos);
    bgDim.setFillColor(sf::Color(0, 0, 0, 80));

    title.setPosition(sf::Vector2f(topLeftPos.x + 260, topLeftPos.y + 10));
    titleSeparator.setPosition(sf::Vector2f(topLeftPos.x + 170, topLeftPos.y + 80));

    selector.setFontSize(50);
    selector.setString(">                           <");
    selector.setPosition(sf::Vector2f(topLeftPos.x + 250 + selectedOption * 100, topLeftPos.y + 120 + selectedOption * 100));

    for (int i = 0; i < nOptions; i++) {
        sf::Vector2f dims = menuOptions[i].getDims();
        menuOptions[i].setPosition(sf::Vector2f(
                    topLeftPos.x + 150 + i * 100 + (288 - dims.x / 2), 
                    topLeftPos.y + 120 + i * 100));
    }

    bool isOpen = true;
    sf::Time frameDelta;
    float dt;
    float blinkTimer = blinkDuration;
    sf::Event event;
    while (isOpen && !shouldClose) {
        frameDelta = clock.restart();
        dt = frameDelta.asMilliseconds();
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                isOpen = false;
                shouldClose = true;
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Key::W:
                    moveSelector(-1);
                    break;
                case sf::Keyboard::Key::S:
                    moveSelector(1);
                    break;
                case sf::Keyboard::Key::E:
                    if (selectedOption == 0) { 
                        isOpen = false; 
                        playCloseAnim(window, clock, viewport);
                    } else if (selectedOption == nOptions - 1) {
                        isOpen = false; 
                        shouldClose = true; 
                    }
                    break;
                case sf::Keyboard::Key::Escape:
                    isOpen = false;
                    playCloseAnim(window, clock, viewport);
                }
                break;
            }
        }
        blinkTimer -= dt;
        if (blinkTimer < 0) {
            if (selector.getString() == "") {
                selector.setString(">                           <");
            } else {
                selector.setString("");
            }
            blinkTimer += blinkDuration;
        } 
        // Drawing
        window.clear(sf::Color(51, 51, 51));
        window.draw(bgSprite);
        window.draw(bgDim);
        window.draw(bgRibbon);
        window.draw(title);
        window.draw(titleSeparator);
        window.draw(selector);
        for (int i = 0; i < nOptions; i++) {
            window.draw(menuOptions[i]);
        }
        window.display();
    }
    return shouldClose;
}
