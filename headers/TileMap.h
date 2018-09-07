#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "../libs/include/TMXParser.h"
#include "../libs/include/TSXParser.h"
#include "./Obstacle.h"
#include "./Animation.h"

class Animation;
class Obstacle;
// See Obstacle.h for details on cell linking
class CellDoor;
// Object that contains and generates all map data such as tiles,
// map objects and tile sets
// Args:
// path - relative path to the map directory
// obstacles - reference to the obstacle list from main.cpp where all obstacles will be added
class TileMap {
public:
    TileMap(std::string path, std::vector<Obstacle> &obstacles, std::vector<CellDoor> &cellDoors);
    ~TileMap();

    void printData();
    void update(float dt);
    void drawAnimatedTerrain(sf::RenderWindow &window);
    // Size in tiles, size in pixels can be aquired
    // Through mapTexture.getSize()
    sf::Vector2i getSize();
    // Texture for sprite that will be used as background
    sf::Texture mapTexture;
    // Texture for sprite that bill be used as foreground
    sf::Texture foreGroundTexture;

    sf::IntRect getViewportRect(sf::Vector2f viewportPos);

private:
    TMX::Parser tmx;
    
    // Generates the background sprite
    sf::Texture generateMap();
    std::vector<sf::Texture> terrainAnimationTexures;
    std::vector<Animation> terrainAnimations;
    std::vector<TerrainAnimation> animSprites;
    
    sf::Image tileSetTexture;
    
    std::string path;
    std::string tileSetPath;

    int tileSize;
    int tileMargin;

    int tileSetWidth;
    int tileSetHeight;

    int width;
    int height;

};

void printVec(std::vector< std::vector<int> > vec);
