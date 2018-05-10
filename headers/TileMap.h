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
    
    sf::Texture generateMap();
    sf::Texture mapTexture;
    
    sf::Image tileSetTexture;
    
    std::string path;
    std::string tileSetPath;

    int tileSize;
    int tileMargin;

    int xAmount;
    int yAmount;

};

void printVec(std::vector< std::vector<int> > vec);