#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "../headers/DevConsole.h"
#include "../headers/Player.h"
#include "../headers/Settings.h"


DevConsole::DevConsole(Settings &settings):
settings(settings) {
    // DevConsole.window kanske behöver lagra en referens
    // Samma med player

    fontFace.loadFromFile("./font.ttf");
}

DevConsole::~DevConsole() {

}

void DevConsole::open(sf::RenderWindow &window, Player &player) {

    bool isOpen = true;
    sf::Event event;
    sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x, 125.0f));
    rectangle.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
    rectangle.setFillColor(sf::Color(70, 70, 70, 150));

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
    text.setPosition(window.mapPixelToCoords(sf::Vector2i(20, 20)));
    text.setColor(sf::Color::White);

    while (isOpen) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isOpen = false;
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if ((event.text.unicode <= 122 && event.text.unicode >= 97) || (event.text.unicode == 32) || (event.text.unicode >= 48 && event.text.unicode <= 57)) {
                    currLine += (char) event.text.unicode;
                } else if (event.text.unicode == 8) {
                    if (currLine.size() > 0) {
                        currLine.pop_back();
                    }
                }
            } else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code)
                {
                    case sf::Keyboard::Key::F2:
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
        text.setString(currLine);

        // blit menu and text
        window.draw(oldTextHolder);
        window.draw(rectangle);
        window.draw(text);
        window.display();
    }

}

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
    }
    
    if (words.size() == 4) {
        if (words[0] == "tp") {
            if (words[1] == "player") {
                player.setPos(sf::Vector2f(std::stof(words[2]), std::stof(words[3])));
                
            }
        }
    }
}