#include "../headers/TileMap.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../libs/include/TMXParser.h"
#include "../libs/include/TSXParser.h"

TileMap::TileMap(std::string path) {
    this->path = path;
    tmx.load("./resources/testMap1.tmx");

    std::cout << "Map Version: " << tmx.mapInfo.version << std::endl;
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
    // TSX-Parsing
    for (int i = 0; i < tmx.tilesetList.size(); i++) {
        std::cout << "Tileset[ First GID: " << tmx.tilesetList[i].firstGID << " Source: " << tmx.tilesetList[i].source << " ]" << std::endl;
        TSX::Parser tsx;
        const char *c = ("./resources/" + tmx.tilesetList[i].source).c_str();
        tsx.load(c);


        std::cout << "Name: " << tsx.tileset.name << std::endl;
    }
}