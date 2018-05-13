# pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Player.h"

class DevConsole {
public:
    DevConsole(Player &player);
    ~DevConsole();

    void open(sf::RenderWindow window);

private:
    sf::Font fontFace;
    std::string currLine;

    Player &player;
};
