#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

struct Node {
    std::vector<Node*> neighbours;
    float startDistance; // G Score
    float endDistance; // F Score
    int x;
    int y;

    bool walkable = true;
};

class Pathfinder {
public:
    Pathfinder();
    ~Pathfinder();
    void generateGraph(std::vector<std::vector<bool>> tiles);
    void setStartNode(int x, int y);
    void setEndNode(int x, int y);
    void generateGraphTexture();
    void draw(sf::RenderWindow &window);

private:
    void sortQueue();

    Node *startNode;
    Node *targetNode;
    std::vector<std::vector<Node>> allNodes;
    std::vector<Node*> closedNodes;
    std::vector<Node*> openNodes; // Priorityqueue

    sf::RenderTexture graphTexture;
    sf::Sprite graphSprite;
};
