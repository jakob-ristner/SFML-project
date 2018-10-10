#pragma once
#include <SFML/Graphics.hpp>
#include "./Settings.h"
#include "./Animation.h"
#include <iostream>

// Abstract class representing a ui interface
class UiElement: public sf::Drawable {
public:
    UiElement();
    ~UiElement();
    virtual void move(sf::Vector2f distance)=0;
    virtual void setPosition(sf::Vector2f pos)=0;
    void toggleDebugMode();
    sf::Font mainFont;
    bool debugMode = false;

protected:
    sf::Vector2f position;
};

// Class representing and implementing the players spell
// casting progress bar
class CastBar: public UiElement {
public:
    CastBar();
    ~CastBar();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void move(sf::Vector2f distance);
    void setPosition(sf::Vector2f pos);
    void update(float newProgress, float castTime, bool isCasting);

private:
    sf::RectangleShape foreground;
    sf::RectangleShape background;

    float progress;
    float castTime;

    bool casting;
};

// Class representing a ui text
// Works as a wrapper for sf::Text with some added functionality
class UiText: public UiElement {
public:
    UiText();
    UiText(sf::Text text);
    ~UiText();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    // Exposing sf::Text's functions to UiText
    void move(sf::Vector2f distance);
    void setPosition(sf::Vector2f pos);
    void setString(std::string str);
    void setFillColor(sf::Color color);
    void setFont(sf::Font &font);
    void setFontSize(unsigned int size);
    void setRotation(float angle) { text.setRotation(angle); }

    sf::Vector2f getDims();
    sf::Vector2f getPosition() { return text.getPosition(); }
    sf::Text getText() {return text;}
    std::string getString() {return text.getString();}

private:
    sf::Text text;
};

class SpellBarIcon: public UiElement {
public:
    SpellBarIcon();
    SpellBarIcon(int id);
    ~SpellBarIcon();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void move(sf::Vector2f distance);
    void setPosition(sf::Vector2f pos);
    void setSelected(bool isSelected);
    void setFont(sf::Font &font);
    void update();
    void setCooldown(float cooldownPercent);
    sf::Vector2f getPosition() ;
    sf::Vector2f getSize();
    UiText *getText();
    sf::RectangleShape *getCooldownRect();

private: // Some of these are temporary
    bool selected;
    int slotId;
    float cooldownPercent;

    sf::RectangleShape cooldownRect;
    sf::RectangleShape background;

    UiText slotIdText;
};

class SpellBar: public UiElement {
public:
    SpellBar();
    SpellBar(int amount);
    ~SpellBar();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void move(sf::Vector2f distance);
    void setPosition(sf::Vector2f pos);

    void setSize(sf::Vector2f size);
    void changeSelection(unsigned short int id);
    void setSpellIcons(std::vector<SpellBarIcon> newIcons);
    void update();
    
    sf::Vector2f getSize();
    sf::Vector2f getPosition() {return position;}

    std::vector<SpellBarIcon>* getIcons();

private:
    std::vector<SpellBarIcon> icons;
    sf::Vector2f size;
    sf::RectangleShape background;
    unsigned short int selected;
};

class PlayerStatBar: public UiElement {
public:
    PlayerStatBar();
    ~PlayerStatBar();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void move(sf::Vector2f distance);
    void setPosition(sf::Vector2f pos);

    void update(float newStat);
    void setMaxStat(float newStat);
    
protected:
    sf::RectangleShape background;
    sf::RectangleShape foreground;
    UiText statText;
    
    float stat;
    float maxStat;
};

class PlayerHpBar: public PlayerStatBar {
public:
    PlayerHpBar();
    ~PlayerHpBar();
};

class PlayerManaBar: public PlayerStatBar {
public:
    PlayerManaBar();
    ~PlayerManaBar();
};

class PlayerStaminaBar: public PlayerStatBar {
public:
    PlayerStaminaBar();
    ~PlayerStaminaBar();
};

class PlayerLevelIcon: public UiElement {
public:
    PlayerLevelIcon();
    ~PlayerLevelIcon();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void move(sf::Vector2f distance);
    void setPosition(sf::Vector2f pos);

    void update(float newLevel);

private:
    int level;
    sf::CircleShape background;
    sf::RenderTexture bgTexture;
    sf::Sprite bgSprite;
    UiText levelText;
};

class UiGrid: public UiElement {
public:
    UiGrid();
    ~UiGrid();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void move(sf::Vector2f distance);
    void setPosition(sf::Vector2f pos);
    void setVisibility(bool newVisible);
    void setXLines(int amount);
    void setYLines(int amount);
    void render();
    void setColor(sf::Color color);

    bool isVisible();

private:
    sf::RenderTexture text;
    sf::Sprite sprite;
    sf::Color lineColor;

    bool visible;
    int xAmount;
    int yAmount;
};

class DropDownMenu: public UiElement {
public:
    DropDownMenu();
    ~DropDownMenu();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void move(sf::Vector2f distance);
    void setPosition(sf::Vector2f pos);
    void setOptions(std::vector<std::string> options);
    void toggleExpand();
    void onClickEvent(sf::Vector2f pos);

    std::string getSelectedOption();
private:
    bool expanded = false;
    sf::RectangleShape background;
    UiText downArrow;
    UiText selectedOption;
    UiText allOptions;
    std::vector<std::string> options;
    std::vector<sf::RectangleShape> debugShapes;
};

class StatusMessage {
public:
    StatusMessage();
    ~StatusMessage();
    virtual void update(float dt);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states);
    virtual std::string getMessage();
    bool kill;
protected:
    float duration;
    std::string message;
};


class CoolDownMessage: public StatusMessage {
public:
    CoolDownMessage();
    ~CoolDownMessage();
    void update(float dt) override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) override;
    std::string getMessage();

};

class PauseMenu {
public:
    PauseMenu(Settings *settings);
    ~PauseMenu();
    bool open(sf::RenderWindow &window, sf::Clock &clock, sf::View &viewport);

private:
    void moveSelector(int dir);
    bool playSlideAnim(sf::RenderWindow &window, sf::Clock &clock, 
                       sf::View &viewport, int ribbonPos, int ribbonEndPos,
                       float startOpacity, float finalOpacity);
    bool playStartAnim(sf::RenderWindow &window, sf::Clock &clock,
                       sf::View &viewport);
    bool playCloseAnim(sf::RenderWindow &window, sf::Clock &clock,
                       sf::View &viewport);

    sf::Sprite bgSprite;
    sf::Texture bgTexture;
    sf::RectangleShape bgRibbon;
    sf::RectangleShape bgDim;
    sf::RectangleShape titleSeparator;

    sf::Vector2f topLeftPos;
    sf::Vector2f viewCenter;

    UiText title;
    UiText selector;
    std::vector<UiText> menuOptions;

    int selectedOption = 0;
    const int nOptions = 4;
    float blinkDuration = 2000;
    float blinkTimer = blinkDuration;
    float ribbonAngle = -20;

    Settings *settings;
};

class SettingsMenu {
public:
    SettingsMenu(Settings *settings);
    ~SettingsMenu();

    bool open(sf::RenderWindow &window, sf::Clock &clock, sf::View &viewport);
    void openGraphicsTab();
    void openControlsTab();
    void toggleDebugMode();

private:
    bool debugMode = false;
    Settings *settings;
    std::string openTab;
    sf::RectangleShape background;
    sf::RectangleShape inactiveTabs;
    sf::RectangleShape activeTab;
    sf::Sprite bgSprite;
    sf::Texture bgTexture;
    sf::Vector2f topLeftPos;
    sf::Vector2f viewCenter;
    // Tab 1
    UiText graphicsTitle;
    UiText resolution;
    DropDownMenu resolutionOptions;
    std::vector<std::string> resOptions;
    sf::FloatRect graphicsTitleClickBox;
    // Tab 2
    UiText controlsTitle;
    sf::FloatRect controlsTitleClickBox;
};
