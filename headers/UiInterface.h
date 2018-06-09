#pragma once
#include <SFML/Graphics.hpp>
#include "./Settings.h"

class UiElement: public sf::Drawable {
public:
    UiElement();
    ~UiElement();
    //virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void move(sf::Vector2f distance)=0;
    virtual void setPosition(sf::Vector2f pos)=0;

protected:
    sf::Vector2f position;
};

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
    void setFont(sf::Font font);

private:
    sf::Text text;
};
