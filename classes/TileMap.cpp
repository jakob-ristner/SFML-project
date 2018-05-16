#include "../headers/TileMap.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

#include "../libs/include/TMXParser.h"
#include "../libs/include/TSXParser.h"
#include "../headers/Obstacle.h"

TileMap::TileMap(std::string path, std::vector<Obstacle> &obstacles) {
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
    
    // Generating objects
    std::string line;
    std::ifstream myfile(path + "/collData.txt");
    while (std::getline(myfile, line)) {
        std::istringstream iss(line);
        float x, y, w, h;
        std::string t;
        if (!(iss >> t >> x >> y >> w >> h)) {
            break;
        }
        //std::cout << x << " " << y << " " << w << " " << h << std::endl;
        obstacles.push_back(Obstacle(sf::Vector2f(x + w / 2.0f, y + h / 2.0f), sf::Vector2f(w, h)));
    }

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
    std::string c;
    for (std::map<std::string, TMX::Parser::TileLayer>::iterator it = tmx.tileLayer.begin(); it != tmx.tileLayer.end(); it++) {
        c = tmx.tileLayer[it->first].data.contents;
        // std::cout << c << std::endl;
        layers.push_back(c);
    }
    // TODO: Allow multiple layers in tileMap
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
    // Width + height in tiles
    width = imgIndexes[imgIndexes.size() - 1].size();
    height = imgIndexes.size() / layers.size();
    // Image for copy and pasting tiles
    sf::Image mapImg;
    mapImg.create(width * tileSize, height * tileSize, sf::Color(0, 0, 0));
    // Copy-pasting all tiles from all layers to correct position
    for (int l = 0; l < layers.size(); l++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (imgIndexes[y + l * height][x]) {
                    // std::cout << "XFLAG: " << x << " " << y << " " << l << std::endl;
                    mapImg.copy(tileSetTexture, 
                    x * tileSize, y * tileSize, 
                    sf::IntRect(((imgIndexes[y + l * height][x] - 1) % (tileSetWidth)) * (tileMargin + tileSize) - tileMargin, 
                    (imgIndexes[y + l * height][x] / tileSetWidth) * (tileSize + tileMargin) - tileMargin, 
                    tileSize, 
                    tileSize
                    ), true);
                    // std::cout << "DONE COPYING: " << x << " " << y << " " << l << std::endl;            
                }
            }
        }
    }

    sf::Texture txt;
    txt.loadFromImage(mapImg);
    return txt;
}

sf::Vector2i TileMap::getSize() {
    return sf::Vector2i(width, height);
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
