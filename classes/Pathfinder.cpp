#include "../headers/Pathfinder.h"

Pathfinder::Pathfinder() {

}

Pathfinder::~Pathfinder() {

}

void Pathfinder::generateGraph(std::vector<std::vector<bool>> inpTiles, int resolutionMult) {
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
            curr->neighbours.push_back(target);
        }
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

}

void Pathfinder::setEndNode(int x, int y) {

}

void Pathfinder::sortQueue() {

}

void Pathfinder::generateGraphTexture() {
    graphTexture.create(allNodes[0].size() * 32, allNodes.size() * 32);
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

void Pathfinder::draw(sf::RenderWindow &window) {
    window.draw(graphSprite);
}
