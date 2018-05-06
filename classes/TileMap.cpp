#include "../headers/TileMap.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../libs/include/TMXParser.h"
#include "../libs/include/TSXParser.h"

TileMap::TileMap(std::string path) {
    this->path = path;
    tmx.load("./resources/testMap1.tmx");

    //std::cout << "Map Version: " << tmx.mapInfo << std::endl;
}

TileMap::~TileMap() {

}