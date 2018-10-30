#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>
#include <climits>

struct Node {
    std::vector<Node*> neighbours;
    float startDistance = std::numeric_limits<float>::infinity(); // G Score
    float endDistance = std::numeric_limits<float>::infinity(); // H Score
    int x;
    int y;

    bool walkable = true;
    Node *cameFrom;
};

class Pathfinder {
public:
    Pathfinder();
    ~Pathfinder();
    void generateGraph(std::vector<std::vector<bool>> inpTiles, float resolutionMult);
    void setStartNode(int x, int y);
    void setEndNode(int x, int y);
    void generateGraphTexture();
    void generatePathTexture();
    void draw(sf::RenderWindow &window);
    void findPath();

private:
    void calcHValues();
    void queuePush(Node *node);
    void reconstuctPath();
    Node *queuePop();
    float calcHValue(Node *node);
    bool isNodeClosed(Node *node);
    bool isNodeOpen(Node *node);

    Node *startNode;
    Node *targetNode;
    std::vector<std::vector<Node>> allNodes;
    std::vector<Node*> closedNodes;
    std::vector<Node*> openNodes; // Priorityqueue - lowest f score first

    sf::RenderTexture graphTexture;
    sf::Sprite graphSprite;
    sf::RenderTexture pathTexture;
    sf::Sprite pathSprite;

    float vertexDistance;

    std::vector<Node*> path;
};
