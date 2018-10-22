#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

#include "../libs/include/TMXParser.h"
#include "../libs/include/TSXParser.h"
#include "../headers/TileMap.h"
#include "../headers/Obstacle.h" 
#include "../headers/Utils.h"
#include "../headers/Obstacle.h"
#include "../headers/Settings.h"

TileMap::TileMap(std::string path, std::vector<Obstacle> &obstacles, std::vector<CellDoor> &cellDoors) {
    this->path = path;
    tileSize = 32;
    tileMargin = 0;
    tmx.load((path + "/tileData.tmx").c_str());

    // TODO: Add dynamic tileSets
    tileSetPath = "./resources/terrain_atlas.png"; //+ tmx.tilesetList[0].source;
    tileSetTexture;
    tileSetTexture.loadFromFile(tileSetPath);

    sf::Vector2u size = tileSetTexture.getSize();
    tileSetWidth = (size.x - tileMargin) / (tileSize + tileMargin);
    tileSetHeight = (size.y - tileMargin) / (tileSize + tileMargin);

    mapTexture = generateMap();
    obstacles.clear();
    cellDoors.clear();
    
    // Generating animations
    std::string line = "";
    std::ifstream anims(path + "/animData.txt");
    while (std::getline(anims, line)) {
        // Read Animation data
        std::vector<std::string> words;
        std::istringstream iss(line);
        do {
            std::string buffer;
            iss >> buffer;
            words.push_back(buffer);
        } while (iss);
        std::string textSource = words[0];
        float animLength, frameCount;
        animLength = std::stof(strSplit(words[1], '|')[1]);
        frameCount = std::stof(strSplit(words[2], '|')[1]);
        terrainAnimationTexures.push_back(sf::Texture());
        terrainAnimationTexures.back().loadFromFile("./resources/terrain_textures/" + textSource);
        sf::Vector2u txtSize = terrainAnimationTexures.back().getSize();
        sf::Vector2f flSize(txtSize.x / frameCount, txtSize.y);
        terrainAnimations.push_back(
                Animation(terrainAnimationTexures.back(), flSize,
                          animLength, 0, frameCount, 0)
        );
    }
    // Generating objects
    line = "";
    std::ifstream myfile(path + "/collData.txt");
    while (std::getline(myfile, line)) {
        std::vector<std::string> words;
        std::istringstream iss(line);
        do {
            std::string buffer;
            iss >> buffer;
            words.push_back(buffer);
        } while (iss);
        float x, y, w, h;
        x = std::stof(words[1]);
        y = std::stof(words[2]);
        w = std::stof(words[3]);
        h = std::stof(words[4]);
        std::string t;
        t = words[0];
        // Custom properties
        if (t == "cell_door") {
            auto link = strSplit(words[5], '|');
            auto linkPos = strSplit(words[6], '|');
            auto lxy = strSplit(linkPos[1], ',');
            float lX = std::stof(lxy[0]);
            float lY = std::stof(lxy[1]);
             cellDoors.push_back(CellDoor(sf::Vector2f(x + w / 2.0f, y + h / 2.0f), sf::Vector2f(w, h), "./resources/" + link[1], sf::Vector2f(lX, lY)));
        } else if (t == "wall") {
            obstacles.push_back(Obstacle(sf::Vector2f(x + w / 2.0f, y + h / 2.0f), sf::Vector2f(w, h)));
        } else if (t == "animated_terrain") {
            int index = std::stoi(strSplit(words[5], '|')[1]);
            float scale = std::stof(strSplit(words[6], '|')[1]);
            animSprites.push_back(TerrainAnimation(&(terrainAnimations[index])));
            animSprites.back().setPosition(sf::Vector2f(x + w / 2.0f, y + h / 2.0f));
            animSprites.back().setScale(sf::Vector2f(scale, scale));
        }
    }

    generateNavData(obstacles);
}

TileMap::~TileMap() {

}

void TileMap::printData() {
    // TMX-Parsing
    for (std::map<std::string, TMX::Parser::TileLayer>::iterator it = tmx.tileLayer.begin(); it != tmx.tileLayer.end(); it++) {
        std::cout << std::endl;
        std::cout << "Tile Layer Name: " << it->first << std::endl;
        std::cout << "Layer Size: " << tmx.tileLayer[it->first].property.size() << std::endl;
        if (tmx.tileLayer[it->first].property.size() > 0) {
            for (std::map<std::string, std::string>::iterator it2 = tmx.tileLayer[it->first].property.begin(); it2 != tmx.tileLayer[it->first].property.end(); ++it2) {
                std::cout << "-> " << it2->first << ":" << it2->second << std::endl;
            }
        }

        //std::cout << tmx.tileLayer[it->first].data.contents << std::endl; 
    }

    for( std::map<std::string, TMX::Parser::ImageLayer>::iterator it = tmx.imageLayer.begin(); it != tmx.imageLayer.end(); ++it ) {
    std::cout << std::endl;
    std::cout << "Image Layer Name: " << it->first << std::endl;
    std::cout << "Image Layer Visibility: " << tmx.imageLayer[it->first].visible << std::endl;
    std::cout << "Image Layer Opacity: " << tmx.imageLayer[it->first].opacity << std::endl;
    std::cout << "Image Layer Properties:" << std::endl;
    if( tmx.imageLayer[it->first].property.size() > 0 ) {
      for( std::map<std::string, std::string>::iterator it2 = tmx.imageLayer[it->first].property.begin(); it2 != tmx.imageLayer[it->first].property.end(); ++it2 ) {
        std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
      }
    }
    std::cout << "Image Layer Source: " << tmx.imageLayer[it->first].image.source << std::endl;
    std::cout << "Image Layer Transparent Color: " << tmx.imageLayer[it->first].image.transparencyColor << std::endl;

    }
}

void TileMap::update(float dt) {
    for (int i = 0; i < terrainAnimations.size(); i++) {
        terrainAnimations[i].update(dt);
    }
    for (int i = 0; i < animSprites.size(); i++) {
        animSprites[i].update();
    }
}

void TileMap::drawAnimatedTerrain(sf::RenderWindow &window) {
    for (int i = 0; i < animSprites.size(); i++) {
        animSprites[i].draw(window);
    }
}

// Generates a map from the current state of the TMX parser.
// Handles both object and tile layers, currently with static tile-sets and pathing
// TODO: Make pathing and tilesets dynamic
sf::Texture TileMap::generateMap() {
    std::vector<std::string> layers;
    std::vector<std::string> fgLayers;
    std::string c;
    for (std::map<std::string, TMX::Parser::TileLayer>::iterator it = tmx.tileLayer.begin(); it != tmx.tileLayer.end(); it++) {
        bool isFG = false;
        c = tmx.tileLayer[it->first].data.contents;
        if (tmx.tileLayer[it->first].property.size() > 0) {
            for (std::map<std::string, std::string>::iterator it2 = tmx.tileLayer[it->first].property.begin(); 
                    it2 != tmx.tileLayer[it->first].property.end(); 
                    it2++ ) {
                if (it2->first == "z-index") {
                    isFG = true;
                }
            }
        }
        if (isFG) {
            fgLayers.push_back(c);
        } else {
            layers.push_back(c);
        }
    }
    std::vector< std::vector<int> > imgIndexes;
    std::vector<int> currentLayer;
    std::string buffer;
    // Conversion to matrix of matrices of ints
    for (int l = 0; l < layers.size(); l++) {
        currentLayer.clear();        
        for(int x = 1; x < layers[l].size(); x++) {
            if (layers[l][x] == '\n') {
                imgIndexes.push_back(currentLayer);
                currentLayer.clear();
            } else if (layers[l][x] == ',') {
                currentLayer.push_back(std::stoi(buffer));
                buffer = "";
            } else {
                buffer += layers[l][x];
            }
        }
        imgIndexes[imgIndexes.size() - 1].push_back(std::stoi(buffer));
        buffer = "";
    }
    buffer = "";
    std::vector< std::vector<int> > fgIndexes;
    for (int l = 0; l < fgLayers.size(); l++) {
        currentLayer.clear();        
        for(int x = 1; x < fgLayers[l].size(); x++) {
            if (fgLayers[l][x] == '\n') {
                fgIndexes.push_back(currentLayer);
                currentLayer.clear();
            } else if (fgLayers[l][x] == ',') {
                currentLayer.push_back(std::stoi(buffer));
                buffer = "";
            } else {
                buffer += fgLayers[l][x];
            }
        }
        fgIndexes[fgIndexes.size() - 1].push_back(std::stoi(buffer));
        buffer = "";
    }
    // Width + height in tiles
    width = imgIndexes[imgIndexes.size() - 1].size();
    height = imgIndexes.size() / layers.size();
    // Image for copy and pasting tiles
    sf::Image mapImg;
    mapImg.create(width * tileSize, height * tileSize, sf::Color(0, 0, 0));
    // Foreground image
    sf::Image foreGround;
    foreGround.create(width * tileSize, 
            height * tileSize, 
            sf::Color(0, 0, 0, 0));
    // Copy-pasting all tiles from all layers to correct position
    for (int l = 0; l < layers.size(); l++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (imgIndexes[y + l * height][x]) {
                    mapImg.copy(tileSetTexture, 
                    x * tileSize, y * tileSize, 
                    sf::IntRect(((imgIndexes[y + l * height][x] - 1) % (tileSetWidth)) * (tileMargin + tileSize) - tileMargin, 
                    (imgIndexes[y + l * height][x] / tileSetWidth) * (tileSize + tileMargin) - tileMargin, 
                    tileSize, 
                    tileSize
                    ), true);
                }
            }
        }
    }
    for (int l = 0; l < fgLayers.size(); l++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (fgIndexes[y + l * height][x]) {
                    foreGround.copy(tileSetTexture,
                        x * tileSize, y * tileSize,
                        sf::IntRect(((fgIndexes[y + l * height][x] - 1) % (tileSetWidth)) * (tileMargin + tileSize) - tileMargin,
                        (fgIndexes[y + l * height][x] / tileSetWidth) * (tileSize + tileMargin) - tileMargin,
                        tileSize,
                        tileSize),
                        true);
                }
            }
        }
    }

    foreGroundTexture.loadFromImage(foreGround);
    sf::Texture txt;
    txt.loadFromImage(mapImg);
    return txt;
}

sf::Vector2i TileMap::getSize() {
    return sf::Vector2i(width, height);
}

sf::IntRect TileMap::getViewportRect(sf::Vector2f viewportPos) {
    float x, y;
    x = viewportPos.x - (settings.WINDOW_WIDTH / 2.0f);
    y = viewportPos.y - (settings.WINDOW_HEIGHT / 2.0f);
    return sf::IntRect(x - 10, y - 10, settings.WINDOW_WIDTH + 20, settings.WINDOW_HEIGHT + 20);
}
// Prints a vector of ints in a pretty format, used in printData
void printVec(std::vector< std::vector<int> > vec) {
    std::string lineBuffer = "";
    for (int y = 0; y < vec.size(); y++) {
        lineBuffer = "[";
        for (int x = 0; x < vec[y].size(); x++) {
            lineBuffer += std::to_string(vec[y][x]) + ",";
        }
        lineBuffer += "]";
        std::cout << lineBuffer << std::endl;
    }
}


// Generates an approximated version of all non-walkable tiles. Also adds 
// padding around these to prevent enemies from snagging on corners.
// Args:
// obstacles - reference to the obstacles which the navData will be generated from
void TileMap::generateNavData(std::vector<Obstacle> &obstacles) {
    navData.resize(getSize().y);
    for (int y = 0; y < navData.size(); y++) {
        navData[y].resize(getSize().x);
    }
    for (int y = 0; y < navData.size(); y++) {
        for (int x = 0; x < navData[y].size(); x++) {
            navData[y][x] = 1;
        }
    }
    for (Obstacle &obstacle: obstacles) {
        int xOffset, yOffset, oWidth, oHeight;
        oWidth = std::round(obstacle.getSize().x / 32.0);
        oHeight = std::round(obstacle.getSize().y / 32.0);
        // Account for origion being in the middle
        xOffset = std::round((obstacle.getPos().x - 32 * oWidth / 2) / 32.0);
        yOffset = std::round((obstacle.getPos().y - 32 * oHeight / 2) / 32.0);
        //std::cout << obstacle.getPos().x << " " << obstacle.getPos().y << std::endl;
        //std::cout << oWidth << " " << oHeight << std::endl;
        //std::cout << xOffset << " " << yOffset << std::endl;
        //std::cout << navData.size() << " " << navData[0].size() << std::endl;
        for (int y = 0; y < oHeight; y++) {
            for (int x = 0; x < oWidth; x++) {
                navData[y + yOffset][x+ xOffset] = 0;
            }
        }
    }
    //for (int y = 0; y < navData.size(); y++) {
        //for (int x = 0; x < navData[y].size(); x++) {
            //std::cout << navData[y][x] << std::endl;
        //}
    //}
    //std::vector<std::vector<bool>> scaledNavData;
    //scaledNavData.resize()
}
