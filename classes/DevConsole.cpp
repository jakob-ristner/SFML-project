#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#include "../headers/DevConsole.h"
#include "../headers/Player.h"
#include "../headers/Settings.h"
#include "../headers/Npc.h"

DevConsole::DevConsole(Settings &settings, EnemyFactory &enemyFactory, UiGrid *grid, Player *player):
settings(settings), enemyFactory(enemyFactory) {
    fontFace.loadFromFile("./font.ttf");
    uiGrid = grid;
    this->player = player;
    commandPointers.push_back(&DevConsole::noclip);
    commandPointers.push_back(&DevConsole::setcolor);
    commandPointers.push_back(&DevConsole::setplayerval);
    commandPointers.push_back(&DevConsole::setvisible);
    commandPointers.push_back(&DevConsole::setxlines);
    commandPointers.push_back(&DevConsole::setylines);
    commandPointers.push_back(&DevConsole::spawn);
    commandPointers.push_back(&DevConsole::tp);
}

DevConsole::~DevConsole() {

}

// Opens the dev console and renders it over the current screen of the game, pausing it.
// Args:
// window - reference to the game window
// player - reference to the player object
bool DevConsole::open(sf::RenderWindow &window, Player &player) {
    
    // Setting up interface components
    bool isOpen = true;
    window.setKeyRepeatEnabled(true);
    sf::Event event;
    sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x - 40, 125.0f));
    rectangle.setPosition(window.mapPixelToCoords(sf::Vector2i(20, 10)));
    rectangle.setFillColor(sf::Color(70, 70, 70, 200));
    rectangle.setOutlineColor(sf::Color(50, 50, 50, 200));
    rectangle.setOutlineThickness(5.0f);

    sf::RectangleShape cursor(sf::Vector2f(1, 30));
    cursor.setPosition(window.mapPixelToCoords(sf::Vector2i(30, 100)));
    cursor.setFillColor(sf::Color::White);

    sf::Texture oldWindow;
    oldWindow.create(window.getSize().x, window.getSize().y);
    oldWindow.update(window);

    sf::RectangleShape oldTextHolder(sf::Vector2f(window.getSize().x, window.getSize().y)); oldTextHolder.setTexture(&oldWindow);
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
            } else if (event.type == sf::Event::TextEntered) { // Writing
                bool typed = true;
                if (event.text.unicode <= 122 && event.text.unicode >= 97) {
                    // Letters
                    currLine = currLine.substr(0, cursorPos) + std::string(1, (char) event.text.unicode) + currLine.substr(cursorPos);
                } else if (event.text.unicode == 32) {
                    // Space
                    currLine = currLine.substr(0, cursorPos) + std::string(1, (char) event.text.unicode) + currLine.substr(cursorPos);
                } else if (event.text.unicode >= 48 && event.text.unicode <= 57) {
                    // Numbers
                    currLine = currLine.substr(0, cursorPos) + std::string(1, (char) event.text.unicode) + currLine.substr(cursorPos);
                } else if (event.text.unicode == 8) {
                    // Backspace
                    typed = false;
                    if (currLine.size() > 0 && cursorPos > 0) {
                        currLine = currLine.substr(0, cursorPos - 1) + currLine.substr(cursorPos);
                        cursorPos--;
                    }
                } else if (event.text.unicode == 46) {
                    // Period
                    currLine = currLine.substr(0, cursorPos) + std::string(1, (char) event.text.unicode) + currLine.substr(cursorPos);
                } else {
                    typed = false;
                }
                
                if (typed) {
                    cursorPos++;
                }
                
            } else if (event.type == sf::Event::KeyPressed) { // Movement
                switch (event.key.code)
                {
                    case 54:
                        isOpen = false;
                        break;
                    case 85:
                        isOpen = false;
                        break;
                    case sf::Keyboard::Key::Return:
                        newParseCommand();
                        if (currLine != "") {
                            history.push_back(currLine);
                        }
                        currLine = "";
                        cursorPos = 0;
                        break;
                    case sf::Keyboard::Key::Up:
                        if (index >= history.size()) {
                            index = history.size();
                        } else {
                            index++;
                            currLine = history[history.size() - index];
                        }
                        cursorPos = currLine.size();
                        break;
                    case sf::Keyboard::Key::Down:
                        if (index <= 1) {
                            index = 0;
                            currLine = "";
                        } else {
                            index--;
                            currLine = history[history.size() - index];
                        }
                        cursorPos = currLine.size();
                        break;
                    case sf::Keyboard::Key::Left:
                        if (cursorPos > 0) {
                            cursorPos--;
                        }
                        break;
                    case sf::Keyboard::Key::Right:
                        if (cursorPos < currLine.size()) {
                            cursorPos++;
                        }
                    default:
                        break;
                }
            }
        }

        text.setString(currLine);
        sf::Vector2f cursorCoord = text.findCharacterPos(cursorPos);
        cursor.setPosition(cursorCoord);

        // Blit menu and text
        window.draw(oldTextHolder);
        window.draw(rectangle);
        window.draw(text);
        window.draw(cursor);
        // Drawing console history
        for (int i = 1; i < 5 && i <= history.size(); i++) {
            historyPlaceHolder.setString(history[history.size() - i]);
            historyPlaceHolder.setPosition(window.mapPixelToCoords(sf::Vector2i(30, 100 - 20 * i)));
            window.draw(historyPlaceHolder);
        }
        window.display();
    }
    window.setKeyRepeatEnabled(false);
    return true;
}

// Private function called by open to process the players input.
// Also handles potential exceptions and displays them to
// the user.
void DevConsole::newParseCommand() {
    words.clear();
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
    
    int commandIndex;
    try {
        commandIndex = searchCommands(getWord(0));
    } catch (std::invalid_argument e) {
        print(e.what());
        return;
    }
    try {
        (this->*commandPointers[commandIndex])();
    } catch (std::out_of_range e) {
        print(e.what());
    }
}

// Logs a (error) message to the DevConsole for the user to see
void DevConsole::print(std::string message) {
    history.push_back("### " + message + " ###");
}

// Binary search function for finding the index of a given command pointer
int DevConsole::searchCommands(std::string command) {
    // Inclusive start, non-inclusive end
    int start = 0;
    int end = commands.size();
    int middle = (start + end) / 2;
    int prev = -1;
    while (middle != prev) {
        if (commands[middle] > command) {
            end = middle;
        } else {
            start = middle;
        }
        prev = middle;
        middle = (start + end) / 2;
    }
    if (commands[middle] != command) {
        throw std::invalid_argument("Could not find command: " + command);
    } else {
        return middle;
    }
}

// Wrapper for accessing the words vector. 
// Prevents SegFaults
std::string DevConsole::getWord(int index) {
    if (index >= words.size() || index < 0) {
        throw std::out_of_range("Too few arguments provided");
    } else {
        return words[index];
    }
}

// Toggles collision between player and walls
void DevConsole::noclip() {
    settings.playerColliding = !settings.playerColliding;
}

// Sets an attribute of player
void DevConsole::setplayerval() {
    std::string arg1 = getWord(1);
    std::string arg2 = getWord(2);
    if (arg1 == "speedmult") {
        float newMult;
        try {
            newMult = std::stof(arg2);
            (*player).setSpeedMult(newMult);
        } catch (std::invalid_argument e) {
            print("Invalid speed");
        }
    } else if (arg1 == "level") {
        int newLevel;
        try {
            newLevel = std::stof(arg2);
            if (newLevel <= 0) { throw(std::invalid_argument("Negative level")); }
            (*player).setLevel(newLevel);
        } catch (std::invalid_argument e) {
            print("Invalid level");
        }
    } else if (arg1 == "mana") {
        float newMana;
        try {
            newMana = std::stof(arg2);
            if (newMana < 0) { throw(std::invalid_argument("Negative mana")); }
            (*player).setMana(newMana);
        } catch (std::invalid_argument e) {
            print("Invalid mana");
        }
    } else if (arg1 == "maxmana") {
        float newMana;
        try {
            newMana = std::stof(arg2);
            if (newMana < 0) { throw(std::invalid_argument("Negative mana")); }
            (*player).setMaxMana(newMana);
        } catch (std::invalid_argument e) {
            print("Invalid mana");
        }
    } else if (arg1 == "hp") {
        float newHp;
        try {
            newHp = std::stof(arg2);
            if (newHp < 0) { throw(std::invalid_argument("Negative hp")); }
            (*player).setHp(newHp);
        } catch (std::invalid_argument e) {
            print("Invalid hp");
        }
    } else if (arg1 == "maxhp") {
        float newHp;
        try {
            newHp = std::stof(arg2);
            if (newHp < 0) { throw(std::invalid_argument("Negative hp")); }
            (*player).setMaxHp(newHp);
        } catch (std::invalid_argument e) {
            print("Invalid hp");
        }
    }
}

// Sets the visibility of a given UI element
void DevConsole::setvisible() {
    if (getWord(1) == "uigrid") {
        if (getWord(2) == "true") {
            (*uiGrid).setVisibility(true);
        } else if (getWord(2) == "false") {
            (*uiGrid).setVisibility(false);
        }
    }
}

// Sets the amount of vertical lines in the uigrid
void DevConsole::setxlines() {
    if (getWord(1) == "uigrid") {
        try {
            (*uiGrid).setXLines(std::stoi(getWord(2)));
        } catch (std::invalid_argument e) {
            print("Invalid number");
        }
    }
}

// Sets the amount of horizontal lines in the uigrid
void DevConsole::setylines() {
    if (getWord(1) == "uigrid") {
        try {
            (*uiGrid).setYLines(std::stoi(getWord(2)));
        } catch (std::invalid_argument e) {
            print("Invalid number");
        }
    }
}

// Spawns a given npc through the enemyFactory
void DevConsole::spawn() {
    float x, y;
    if (getWord(2) == ".") {
        x = player->getPos().x;
    } else {
        try {
            x = std::stof(getWord(2));
        } catch (std::invalid_argument e) {
            print("Coordinate x could not be parsed");
        }
    }
    if (getWord(3) == ".") {
        y = player->getPos().y;
    } else {
        try {
            y = std::stof(getWord(3));
        } catch (std::invalid_argument e) {
            print("Coordinate y could not be parsed");
        }
    }
    enemyFactory.spawnEnemy(getWord(1), sf::Vector2f(x, y));
}

// Sets the color of a given ui element
void DevConsole::setcolor() {
    if (getWord(1) == "uigrid") {
        try {
            (*uiGrid).setColor(sf::Color(std::stoi(getWord(2)), std::stoi(getWord(3)), std::stoi(getWord(4))));
        } catch (std::invalid_argument e) {
            print("Invalid color argument");
        }
    }
}

// Teleports a given actor
void DevConsole::tp() {
    if (getWord(0) == "tp") {
        if (getWord(1) == "player") {
            float x, y;
            try {
                x = std::stof(getWord(2));
                y = std::stof(getWord(3));
                (*player).setPos(sf::Vector2f(x, y));
            } catch (std::invalid_argument e) {
                print("The x or y provided could not be parsed");
            }
        }
    }
}
