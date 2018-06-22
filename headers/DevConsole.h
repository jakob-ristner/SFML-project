# pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "./Player.h"
#include "./Settings.h"
#include "./Npc.h"
#include "./UiInterface.h"

class DevConsole {
public:
    DevConsole(Settings &settings, EnemyFactory &enemyFactory, UiGrid *grid);
    ~DevConsole();

    bool open(sf::RenderWindow &window, Player &player);

private:
    void parseCommand(Player &player);
    void print(std::string message);

    sf::Font fontFace;
    std::string currLine;
    std::vector<std::string> history;
    Settings &settings;
    EnemyFactory &enemyFactory;
    UiGrid *uiGrid;

    unsigned short int index = 0;
};
