#include <SFML/Graphics.hpp>
#include <string>

#include "../headers/DevConsole.h"
#include "../headers/Player.h"


DevConsole::DevConsole(Player &player) {
    // DevConsole.window kanske behöver lagra en referens
    // Samma med player
    this->player = player;

    fontFace.loadFromFile("../font.ttf");
}

DevConsole::~DevConsole() {

}

void DevConsole::open(sf::RenderWindow window) {
    // Loop that saves window as an Image to display
    // then get line from user (until ENTER)
    // parse line -> call apropriate function
    bool isOpen = true;
    sf::Event event;
    while (isOpen) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                isOpen = false;
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    currLine += (char) event.text.unicode;
                }
            }
        }

        // blit menu and text

        window.display();
    }

}
