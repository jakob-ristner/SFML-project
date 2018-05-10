#pragma once
#include <SFML/Graphics.hpp>

#include "../libs/include/TMXParser.h"
#include "../libs/include/TSXParser.h"

// WARNING: Will only read first tileLayer right now
// Will be fixed

class TileMap {
public:
    TileMap(std::string path);
    ~TileMap();

    sf::Texture mapTexture;
    void printData();

private:
    TMX::Parser tmx;
    
    sf::Texture generateMap();
    
    sf::Image tileSetTexture;
    
    std::string path;
    std::string tileSetPath;

    int tileSize;
    int tileMargin;

    int xAmount;
    int yAmount;

    int width;
    int height;

};

void printVec(std::vector< std::vector<int> > vec);