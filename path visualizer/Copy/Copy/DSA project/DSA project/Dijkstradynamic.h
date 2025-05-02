#pragma once
//#ifndef DIJKSTRA_DYNAMIC_H
//#define DIJKSTRA_DYNAMIC_H
//
//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <unordered_map>
//#include <queue>
//
//struct NodeE {
//    sf::Vector2i position;
//    NodeE* parent = nullptr;
//    float gCost = std::numeric_limits<float>::infinity();  // Cost from start
//    bool operator>(const NodeE& other) const {
//        return gCost > other.gCost;
//    }
//
//    NodeE(const sf::Vector2i& pos) : position(pos) {}
//};
//
//
//
//
//std::vector<sf::Vector2i> dijkstraVisualized(
//    const sf::Vector2i& start,
//    const sf::Vector2i& goal,
//    const std::vector<std::vector<int>>& hurdleMatrix,
//    sf::RenderWindow& window,
//    int tileSize);
//
//void runDijkstraVisualizer();
//
//#endif // DIJKSTRA_DYNAMIC_H

#ifndef DIJKSTRADYNAMIC_H
#define DIJKSTRADYNAMIC_H

#include <SFML/Graphics.hpp>
#include <limits>

struct NodeE {
    sf::Vector2i position;
    NodeE* parent = nullptr;
    float gCost = std::numeric_limits<float>::infinity();  // Correctly using 'infinity'

    // Default constructor
    NodeE() : position(sf::Vector2i(0, 0)), parent(nullptr), gCost(std::numeric_limits<float>::infinity()) {}

    // Constructor with position
    NodeE(const sf::Vector2i& pos) : position(pos), parent(nullptr), gCost(std::numeric_limits<float>::infinity()) {}

    bool operator>(const NodeE& other) const {
        return gCost > other.gCost;
    }
};


// Rest of the code goes here
std::vector<sf::Vector2i> dijkstraVisualized(
    const sf::Vector2i& start,
    const sf::Vector2i& goal,
    const std::vector<std::vector<int>>& hurdleMatrix,
    sf::RenderWindow& window,
    int tileSize);


    void runDijkstraVisualizer();
#endif  // DIJKSTRADYNAMIC_H
