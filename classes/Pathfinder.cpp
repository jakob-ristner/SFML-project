#include "../headers/Pathfinder.h"

Pathfinder::Pathfinder(float thinkInterval) {
    this->thinkInterval = thinkInterval;
}

Pathfinder::~Pathfinder() {

}

void Pathfinder::generateGraph(std::vector<std::vector<bool>> inpTiles, float resolutionMult) {
    std::vector<std::vector<bool>> tiles;
    tiles.resize(inpTiles.size() * resolutionMult);
    for (int y = 0; y < tiles.size(); y++) {
        tiles[y].resize(inpTiles[y/resolutionMult].size() * resolutionMult);
    }
    vertexDistance = 32 / resolutionMult;
    // Insert values from inpTiles
    for(int y = 0; y < inpTiles.size(); y++) {
        for(int x = 0; x < inpTiles[y].size(); x++) {
            for(int y2 = 0; y2 < resolutionMult; y2++) {
                for(int x2 = 0; x2 < resolutionMult; x2++) {
                    tiles[y * resolutionMult + y2][x * resolutionMult + x2] = inpTiles[y][x];
                }
            }
        }
    }
    std::vector<std::vector<bool>> tmp = tiles;
    // Padd edges
    for(int y = 0; y < tiles.size(); y++) {
        for(int x = 0; x < tiles[y].size(); x++) {
            if (!tmp[y][x]) {
                if (y != 0) {
                    if (x != 0) {
                        tiles[y-1][x-1] = false;
                    }
                    tiles[y-1][x] = false;
                    if (x != tiles[y].size() - 1) {
                        tiles[y-1][x+1] = false;
                    }
                }
                if (x != 0) {
                    tiles[y][x-1] = false;
                }
                if (x != tiles[y].size() - 1) {
                    tiles[y][x+1] = false;
                }
                if (y != tiles.size() - 1) {
                    if (x != 0) {
                        tiles[y+1][x-1] = false;
                    }
                    tiles[y+1][x] = false;
                    if (x != tiles[y].size() - 1) {
                        tiles[y+1][x+1] = false;
                    }
                }
            }
        }
    }
    int dataWidth = tiles[0].size();
    int dataHeight = tiles.size();
    allNodes.resize(tiles.size());
    for (std::vector<Node> &row: allNodes) {
        row.resize(tiles[0].size());
    }
    // Settings values for nodes
    for (int y = 0; y < tiles.size(); y++) {
        for (int x = 0; x < tiles[y].size(); x++) {
            allNodes[y][x].x = x;
            allNodes[y][x].y = y;
            allNodes[y][x].walkable = tiles[y][x];
        }
    }
    // Setting neighbours
    Node *curr = &(allNodes[0][0]);
    Node *target = &(allNodes[0][1]);
    // Top Left Corner
    if (curr->walkable) {
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[1][0]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[1][1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
    }
    // Top Right Corner
    curr = &(allNodes[0][dataWidth - 1]);
    if (curr->walkable) {
        target = &(allNodes[0][dataWidth - 2]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[1][dataWidth - 1]);
        if (target->walkable) {
            curr->neighbours.push_back(target); }
        target = &(allNodes[1][dataWidth - 2]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
    }
    // Bottom Left Corner
    curr = &(allNodes[dataHeight-1][0]);
    if (curr->walkable) {
        target = &(allNodes[dataHeight-2][0]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[dataHeight-2][1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[dataHeight-1][1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
    }
    // Bottom Right Corner
    curr = &(allNodes[dataHeight-1][dataWidth-1]);
    if (curr->walkable) {
        target = &(allNodes[dataHeight-2][dataWidth - 1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[dataHeight-2][dataWidth - 2]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[dataHeight-1][dataWidth - 2]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
    }
    // First Row
    for (int x = 1; x < allNodes[0].size() - 1; x++) {
        curr = &(allNodes[0][x]);
        if (!curr->walkable) { continue; }
        target = &(allNodes[0][x-1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[0][x+1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[1][x-1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[1][x]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[1][x+1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
    }
    // Last Row
    for (int x = 1; x < allNodes[dataHeight - 1].size() - 1; x++) {
        curr = &(allNodes[dataHeight - 1][x]);
        if (!curr->walkable) { continue; }
        target = &(allNodes[dataHeight-1][x-1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[dataHeight-1][x+1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[dataHeight-2][x-1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[dataHeight-2][x]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[dataHeight - 2][x+1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
    }
    // First Column
    for (int y = 1; y < allNodes.size() - 1; y++) {
        curr = &(allNodes[y][0]);
        if (!curr->walkable) { continue; }
        target = &(allNodes[y-1][0]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[y+1][0]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[y-1][1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[y][1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[y+1][1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
    }
    // Last Column
    for (int y = 1; y < allNodes.size() - 1; y++) {
        curr = &(allNodes[y][dataWidth-1]);
        if (!curr->walkable) { continue; }
        target = &(allNodes[y-1][dataWidth-1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[y+1][dataWidth-1]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[y-1][dataWidth-2]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[y][dataWidth-2]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
        target = &(allNodes[y+1][dataWidth-2]);
        if (target->walkable) {
            curr->neighbours.push_back(target);
        }
    }

    for (int y = 1; y < allNodes.size() - 1; y++) {
        for (int x = 1; x < allNodes[y].size() - 1; x++) {
            curr = &(allNodes[y][x]);
            if (!curr->walkable) { continue; }
            target = &(allNodes[y-1][x-1]);
            if (target->walkable) {
                curr->neighbours.push_back(target);
            }
            target = &(allNodes[y-1][x]);
            if (target->walkable) {
                curr->neighbours.push_back(target);
            }
            target = &(allNodes[y-1][x+1]);
            if (target->walkable) {
                curr->neighbours.push_back(target);
            }
            target = &(allNodes[y][x-1]);
            if (target->walkable) {
                curr->neighbours.push_back(target);
            }
            target = &(allNodes[y][x+1]);
            if (target->walkable) {
                curr->neighbours.push_back(target);
            }
            target = &(allNodes[y+1][x-1]);
            if (target->walkable) {
                curr->neighbours.push_back(target);
            }
            target = &(allNodes[y+1][x]);
            if (target->walkable) {
                curr->neighbours.push_back(target);
            }
            target = &(allNodes[y+1][x+1]);
            if (target->walkable) {
                curr->neighbours.push_back(target);
            }
        }
    }
}

void Pathfinder::setStartNode(int x, int y) {
    startNode = &(allNodes[y][x]);
}

void Pathfinder::setEndNode(int x, int y) {
    targetNode = &(allNodes[y][x]);
}

void Pathfinder::generateGraphTexture() {
    graphTexture.create(allNodes[0].size() * vertexDistance, allNodes.size() * vertexDistance);
    graphTexture.clear(sf::Color::Transparent);
    sf::Vertex line[2];
    line[0].color = sf::Color::Blue;
    line[1].color = sf::Color::White;
    for (std::vector<Node> &row: allNodes) {
        for (Node &node: row) {
            for (Node *other: node.neighbours) {
                line[0].position = sf::Vector2f(node.x * vertexDistance + vertexDistance / 2, node.y * vertexDistance + vertexDistance / 2);
                line[1].position = sf::Vector2f(other->x * vertexDistance + vertexDistance / 2, other->y * vertexDistance + vertexDistance / 2);
                graphTexture.draw(line, 2, sf::LineStrip);
            }
        }
    }
    graphTexture.display();
    graphSprite.setPosition(sf::Vector2f(0, 0));
    graphSprite.setTexture(graphTexture.getTexture());
}

void Pathfinder::generatePathTexture() {
    pathTexture.create(allNodes[0].size() * vertexDistance, allNodes.size() * vertexDistance);
    pathTexture.clear(sf::Color::Transparent);
    sf::Vertex *line;
    line = (sf::Vertex*) malloc(sizeof(Node) * path.size());
    int i = 0;
    for (Node *node: path) {
        line[i] = sf::Vertex();
        line[i].color = sf::Color::Red;
        line[i].position = sf::Vector2f(node->x * vertexDistance + vertexDistance / 2, node->y * vertexDistance + vertexDistance / 2);
        i++;
    }
    pathTexture.draw(line, path.size(), sf::LineStrip);
    pathTexture.display();
    free(line);
    pathSprite.setPosition(sf::Vector2f(0, 0));
    pathSprite.setTexture(pathTexture.getTexture());
}

void Pathfinder::draw(sf::RenderWindow &window) {
    window.draw(graphSprite);
    window.draw(pathSprite);
}

void Pathfinder::update(float dt) {
    currTime += dt;
    if (currTime >= thinkInterval) {
        currTime -= thinkInterval;
        findPath();
    }
}

std::vector<sf::Vector2f> Pathfinder::getPath() {
    std::vector<sf::Vector2f> output;
    output.resize(path.size());
    Node *node;
    for (int i = 0; i < path.size(); i++) {
        node = path[i];
        output[i] = sf::Vector2f(node->x * vertexDistance, node->y * vertexDistance);
    }
    return output;
}

void Pathfinder::queuePush(Node *node) {
    int i;
    for (i = 0; i < openNodes.size(); i++) {
        if (openNodes[i]->startDistance + openNodes[i]->endDistance > 
                node->startDistance + node->endDistance) {
            break;
        }
    }
    openNodes.insert(openNodes.begin() + i, node);
}

void Pathfinder::reconstuctPath() {
    path.clear();
    Node *curr = targetNode;
    while (curr != startNode) {
        path.push_back(curr);
        curr = curr->cameFrom;
    }
    std::reverse(path.begin(), path.end());
}

Node* Pathfinder::queuePop() {
    Node *tmp = openNodes[0];
    openNodes.erase(openNodes.begin());
    return tmp;
}

float Pathfinder::calcHValue(Node *node) {
    float endX = targetNode->x;
    float endY = targetNode->y;
    return std::pow(endX - node->x, 2) + std::pow(endY - node->y, 2);
}

bool Pathfinder::isNodeClosed(Node *node) {
    for (Node *tmp: closedNodes) {
        if (tmp == node) {
            return true;
        }
    }
    return false;
}

bool Pathfinder::isNodeOpen(Node *node) {
    for (Node *tmp: openNodes) {
        if (tmp == node) {
            return true;
        }
    }
    return false;
}

void Pathfinder::findPath() {
    closedNodes.clear();
    openNodes.clear();
    // Add start node to open nodes
    queuePush(startNode);
    startNode->startDistance = 0;
    bool done = false;
    Node *curr;
    while (!done) {
        curr = queuePop();
        curr->endDistance = calcHValue(curr);
        if (curr == targetNode) {
            done = true;
            break;
        }
        closedNodes.push_back(curr);
        // Add neighbours to open nodes
        for (Node *child: curr->neighbours) {
            if (isNodeClosed(child)) {
                continue;
            }
            float newStartDistance = std::pow(curr->x - child->x, 2) + std::pow(curr->y - child->y, 2);
            // Straight connection
            if (newStartDistance == 1) { newStartDistance = 10; }
            if (newStartDistance == 2) { newStartDistance = 14; }
            // Diagonal connection 14 == sqrt(2) * 10
            newStartDistance += curr->startDistance;
            if (!isNodeOpen(child)) {
                queuePush(child);
            } else if (newStartDistance >= child->startDistance) {
                // Not better path
                continue;
            }

            // Currently on best path
            child->cameFrom = curr;
            child->startDistance = newStartDistance;
        }
    }
    reconstuctPath();
}

EnemyPathfinder::EnemyPathfinder(float thinkInterval) : 
    Pathfinder(thinkInterval) {

}

EnemyPathfinder::~EnemyPathfinder() {

}

void EnemyPathfinder::update(float dt) {
    currTime += dt;
    std::cout << currTime << std::endl;
    if (currTime >= thinkInterval) {
        currTime -= thinkInterval;
        if (std::pow(startNode->x - targetNode->x, 2) + 
            std::pow(startNode->y - targetNode->y, 2) <= 2) {
            path = {startNode, targetNode};
        } else {
            findPath();
        }
        generatePathTexture();
        std::cout << "Kek" << std::endl;
    }
    if (std::pow(startNode->x - targetNode->x, 2) + 
        std::pow(startNode->y - targetNode->y, 2) <= 2) {
        path = {targetNode};
    }
}
