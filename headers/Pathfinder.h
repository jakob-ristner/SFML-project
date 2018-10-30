#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <climits>

struct Node {
    std::vector<Node*> neighbours;
    float startDistance = std::numeric_limits<float>::infinity(); // G Score
    float endDistance; // H Score
    int x;
    int y;

    bool walkable = true;
    Node *cameFrom;
};

class Pathfinder {
public:
    Pathfinder();
    ~Pathfinder();
    void generateGraph(std::vector<std::vector<bool>> inpTiles, int resolutionMult);
    void setStartNode(int x, int y);
    void setEndNode(int x, int y);
    void generateGraphTexture();
    void draw(sf::RenderWindow &window);
    void findPath();

private:
    void calcHValues();
    void updateFValues(Node *parent);
    void queuePush(Node *node);
    Node *queuePop();

    Node *startNode;
    Node *targetNode;
    std::vector<std::vector<Node>> allNodes;
    std::vector<Node*> closedNodes;
    std::vector<Node*> openNodes; // Priorityqueue - lowest f score first

    sf::RenderTexture graphTexture;
    sf::Sprite graphSprite;

    int vertexDistance;
};
