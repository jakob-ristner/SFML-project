#pragma once
#include <SFML/Graphics.hpp>

#include "../libs/include/TMXParser.h"
#include "../libs/include/TSXParser.h"

class TileMap {
public:
    TileMap(std::string path);
    ~TileMap();

    void printData();

private:
    TMX::Parser tmx;
    std::string path;
};