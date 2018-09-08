#pragma once
#include <SFML/Graphics.hpp>
#include "./Settings.h"
#include <iostream>

// Abstract class representing a ui interface
class UiElement: public sf::Drawable {
public:
    UiElement();
    ~UiElement();
    virtual void move(sf::Vector2f distance)=0;
    virtual void setPosition(sf::Vector2f pos)=0;

protected:
    sf::Vector2f position;
    sf::Font mainFont;
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

    sf::Vector2f getDims();
    sf::Text getText() {return text;}

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

    sf::Vector2f getPosition() ;
    void printPos() {std::cout << background.getPosition().x << " " << background.getPosition().y << std::endl;}
    void printSize() {std::cout << background.getSize().x << " " << background.getSize().y << std::endl;}
    UiText *getText();

private: // Some of these are temporary
    bool selected;
    int slotId;

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

private:
    std::vector<SpellBarIcon> icons;
    sf::Vector2f size;
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
