#include "../headers/TileMap.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "../libs/include/TMXParser.h"
#include "../libs/include/TSXParser.h"

TileMap::TileMap(std::string path) {
    this->path = path;
    tileSize = 32;
    tileMargin = 1;
    tmx.load(path.c_str());

    // TODO: Add dynamic tileSets
    tileSetPath = "./resources/tile-set1.png"; //+ tmx.tilesetList[0].source;
    tileSetTexture;
    tileSetTexture.loadFromFile(tileSetPath);

    sf::Vector2u size = tileSetTexture.getSize();
    xAmount = (size.x - tileMargin) / (tileSize + tileMargin);
    yAmount = (size.y - tileMargin) / (tileSize + tileMargin);

    sf::Texture mapTexture = generateMap();
}

TileMap::~TileMap() {

}

void TileMap::printData() {
    // TMX-Parsing
    for (std::map<std::string, TMX::Parser::TileLayer>::iterator it = tmx.tileLayer.begin(); it != tmx.tileLayer.end(); it++) {
        std::cout << std::endl;
        std::cout << "Tile Layer Name: " << it->first << std::endl;
        std::cout << "Layer Size: " << tmx.tileLayer[it->first].property.size() << std::endl;

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

sf::Texture TileMap::generateMap() {
    std::vector<std::string> layers;
    for (std::map<std::string, TMX::Parser::TileLayer>::iterator it = tmx.tileLayer.begin(); it != tmx.tileLayer.end(); it++) {
        std::string c = tmx.tileLayer[it->first].data.contents;
        // std::cout << c << std::endl;
        layers.push_back(c);
    }
    std::vector< std::vector<int> > imgIndexes;
    std::vector<int> currentLayer;
    std::string buffer;
    for (int l = 0; l < layers.size(); l++) {
        currentLayer.clear();        
        for(int x = 0; x < layers[l].size(); x++) {
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
    }
    printVec(imgIndexes);
    return sf::Texture();
}

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