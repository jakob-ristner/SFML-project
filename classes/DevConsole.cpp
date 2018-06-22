#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "../headers/DevConsole.h"
#include "../headers/Player.h"
#include "../headers/Settings.h"
#include "../headers/Npc.h"


DevConsole::DevConsole(Settings &settings, EnemyFactory &enemyFactory):
settings(settings), enemyFactory(enemyFactory) {
    // DevConsole.window kanske behöver lagra en referens
    // Samma med player

    fontFace.loadFromFile("./font.ttf");
}

DevConsole::~DevConsole() {

}

// Opens the dev console and renders it over the current screen of the game, pausing it.
// Args:
// window - reference to the game window
// player - reference to the player object
bool DevConsole::open(sf::RenderWindow &window, Player &player) {

    bool isOpen = true;
    sf::Event event;
    sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x - 40, 125.0f));
    rectangle.setPosition(window.mapPixelToCoords(sf::Vector2i(20, 10)));
    rectangle.setFillColor(sf::Color(70, 70, 70, 200));
    rectangle.setOutlineColor(sf::Color(50, 50, 50, 200));
    rectangle.setOutlineThickness(5.0f);

    sf::Texture oldWindow;
    oldWindow.create(window.getSize().x, window.getSize().y);
    oldWindow.update(window);

    sf::RectangleShape oldTextHolder(sf::Vector2f(window.getSize().x, window.getSize().y));
    oldTextHolder.setTexture(&oldWindow);
    oldTextHolder.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));

    sf::Text text;
    text.setString("");
    text.setScale(sf::Vector2f(0.75f, 0.75f));
    text.setFont(fontFace);
    text.setPosition(window.mapPixelToCoords(sf::Vector2i(30, 100)));
    text.setFillColor(sf::Color::White);

    sf::Text historyPlaceHolder;
    historyPlaceHolder.setString("");
    historyPlaceHolder.setScale(sf::Vector2f(0.75f, 0.75f));
    historyPlaceHolder.setFont(fontFace);
    historyPlaceHolder.setPosition(window.mapPixelToCoords(sf::Vector2i(30, 80)));
    historyPlaceHolder.setFillColor(sf::Color(210, 210, 210));

    index = 0;
    while (isOpen) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isOpen = false;
                return false;
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode <= 122 && event.text.unicode >= 97) {
                    // Letters
                    currLine += (char) event.text.unicode;
                } else if (event.text.unicode == 32) {
                    // Space
                    currLine += (char) event.text.unicode;
                } else if (event.text.unicode >= 48 && event.text.unicode <= 57) {
                    // Numbers
                    currLine += (char) event.text.unicode;
                } else if (event.text.unicode == 8) {
                    // Backspace
                    if (currLine.size() > 0) {
                        currLine.pop_back();
                    }
                } else if (event.text.unicode == 46) {
                    // Period
                    currLine += (char) event.text.unicode;
                }
                
            } else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code)
                {
                    case 54:
                        isOpen = false;
                        break;
                        case sf::Keyboard::Key::Return:
                        parseCommand(player);
                        if (currLine != "") {
                            history.push_back(currLine);
                        }
                        currLine = "";
                        break;
                    case sf::Keyboard::Key::Up:
                        if (index >= history.size()) {
                            index = history.size();
                        } else {
                            index++;
                            currLine = history[history.size() - index];
                        }
                        break;
                    case sf::Keyboard::Key::Down:
                        if (index <= 1) {
                            index = 0;
                            currLine = "";
                        } else {
                            index--;
                            currLine = history[history.size() - index];
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        


        text.setString(currLine + "_");

        // blit menu and text
        window.draw(oldTextHolder);
        window.draw(rectangle);
        window.draw(text);
        // Drawing console history
        for (int i = 1; i < 5 && i <= history.size(); i++) {
            historyPlaceHolder.setString(history[history.size() - i]);
            historyPlaceHolder.setPosition(window.mapPixelToCoords(sf::Vector2i(30, 100 - 20 * i)));
            window.draw(historyPlaceHolder);
        }
        window.display();
    }
    return true;
}

// Parses an entered command and calls the apropriate function(s)
// Args:
// player - reference to the player object
void DevConsole::parseCommand(Player &player) {
    std::vector<std::string> words;
    std::string buffer;

    for (int i = 0; i < currLine.length(); i++) {
        if (currLine[i] == ' ') {
            words.push_back(buffer);
            buffer = "";
        } else {
            buffer += currLine[i];
        }
    }
    words.push_back(buffer);
    buffer = "";

    if (words.size() == 1) {
        if (words[0] == "noclip") {
            settings.playerColliding = !settings.playerColliding;
        }
    } else if (words.size() == 3) {
        if (words[0] == "setlevel") {
            if (words[1] == "player") {
                int newLevel;
                try {
                    newLevel = std::stoi(words[2]);
                } catch (std::invalid_argument e) {
                    newLevel = player.getLevel();
                }
                player.setLevel(newLevel);
            }
        }
    }

    // Implement this part as a binary search
    // Improves runtime efficiency and looks prettier
    else if (words.size() == 4) {
        if (words[0] == "tp") {
            if (words[1] == "player") {
                player.setPos(sf::Vector2f(std::stof(words[2]), std::stof(words[3])));
                
            }
        } else if (words[0] == "spawn") {
            float x;
            float y;
            if (words[2] == ".") {
                x = player.getPos().x;
            } else {
                x = std::stof(words[2]);
            }
            if (words[3] == ".") {
                y = player.getPos().y;
            } else {
                y = std::stof(words[3]);
            }
            enemyFactory.spawnEnemy(words[1], sf::Vector2f(x, y));

        }
    }
}
