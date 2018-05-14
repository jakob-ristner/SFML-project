# pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Player.h"
#include "Settings.h"

class DevConsole {
public:
    DevConsole(Settings &settings);
    ~DevConsole();

    bool open(sf::RenderWindow &window, Player &player);

private:
    void parseCommand(Player &player);

    sf::Font fontFace;
    std::string currLine;
    std::vector<std::string> history;
    Settings &settings;

    unsigned short int index = 0;
};
