#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>
#include <climits>
#include "./Player.h"

struct Node {
    std::vector<Node*> neighbours;
    float startDistance = std::numeric_limits<float>::infinity(); // G Score
    float endDistance = std::numeric_limits<float>::infinity(); // H Score
    float prev = std::numeric_limits<float>::infinity();
    int x;
    int y;

    bool walkable = true;
    bool inRange = true;
    Node *cameFrom;
};

class Pathfinder {
public:
    Pathfinder(float thinkInterval);
    ~Pathfinder();
    void generateGraph(std::vector<std::vector<bool>> inpTiles, float resolutionMult);
    void setStartNode(int x, int y);
    void setEndNode(int x, int y);
    void generateGraphTexture();
    void generatePathTexture();
    void draw(sf::RenderWindow &window);
    void update(float dt);
    std::vector<sf::Vector2f> getPath();

protected:
    void queuePush(Node *node);
    void reconstuctPath();
    Node *queuePop();
    float calcHValue(Node *node);
    bool isNodeClosed(Node *node);
    bool isNodeOpen(Node *node);
    void findPath();
    void findPath2();

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

    // Timer stuff
    float currTime = 0;
    float thinkInterval;
};

class EnemyPathfinder : public Pathfinder {
public:
    EnemyPathfinder(float thinkInterval);
    ~EnemyPathfinder();

    void update(float dt, sf::Vector2f enemyPos, sf::Vector2f playerPos);
    void setAggroRange(float distance);
    void setMap(std::vector<std::vector<bool>> inpTiles);
    
protected:
    void updateRanges();
    float getTotalCost();

    float aggroRange = std::numeric_limits<float>::infinity();
    sf::Vector2i position;
};
