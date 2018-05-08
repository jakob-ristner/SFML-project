#include "../headers/TileMap.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../libs/include/TMXParser.h"
#include "../libs/include/TSXParser.h"

TileMap::TileMap(std::string path) {
    this->path = path;
    tileSize = 32;
    tileMargin = 1;
    tmx.load("./resources/testMap1.tmx");

    // TODO: Add dynamic tileSets
    std::string tileSetPath = "./resources/tile-set1.png"; //+ tmx.tilesetList[0].source;
    sf::Texture tileSetTexture;
    tileSetTexture.loadFromFile(tileSetPath);

    sf::Vector2u size = tileSetTexture.getSize();
    int xAmount = (size.x - tileMargin) / (tileSize + tileMargin);
    int yAmount = (size.y - tileMargin) / (tileSize + tileMargin);

    generateMap();
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
    std::cout << tmx.tileLayer[0].data.contents << std::endl;
}
