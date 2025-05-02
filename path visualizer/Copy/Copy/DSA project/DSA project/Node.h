#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

struct Node {
    int x, y;                          // Grid coordinates
    float gCost = 0, hCost = 0;        // Costs for A* algorithm
    bool isObstacle = false;           // For hurdle maze
    bool isVisited = false;            // Pathfinding flag
    bool isHurdle = false;             // Hurdle flag
    std::pair<int, int> position;      // Coordinates as a pair
    Node* parent = nullptr;            // Pointer to reconstruct the path

    // Numeric Weighted Maze fields
    sf::Vector2i positionVector;       // Position in SFML grid
    std::vector<Node*> neighbors;      // Adjacent nodes for graph
    int weight = 0;                    // Weight for numeric maze
    bool hasWeight = false;            // Whether node has a weight

    // Total cost (used for A* and Dijkstra)
    float fCost() const { return gCost + hCost; }
};
