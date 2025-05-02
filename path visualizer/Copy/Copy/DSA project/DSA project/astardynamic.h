#ifndef ASTARVISUALIZER_H
#define ASTARVISUALIZER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>

// Node structure for A* algorithm
struct NodeS {
    sf::Vector2i position;
    float gCost = 0;
    float hCost = 0;
    NodeS* parent = nullptr;

    float getFCost() const {
        return gCost + hCost;
    }

    bool operator<(const NodeS& other) const {
        return getFCost() > other.getFCost();
    }
};

// Function declarations
//std::vector<sf::Vector2i> aStarVisualized(
//    const sf::Vector2i& start,
//    const sf::Vector2i& goal,
//    const std::vector<std::vector<int>>& hurdleMatrix,
//    sf::RenderWindow& window,
//    int tileSize);

std::vector<sf::Vector2i> aStarVisualized(
    const sf::Vector2i& start,
    const sf::Vector2i& goal,
    const std::vector<std::vector<int>>& hurdleMatrix,
    sf::RenderWindow& window,
    int tileSize,
    int& totalExpandedNodes
);

void runAStarVisualizer(); // Wrapper function for visualization

#endif // ASTARVISUALIZER_H