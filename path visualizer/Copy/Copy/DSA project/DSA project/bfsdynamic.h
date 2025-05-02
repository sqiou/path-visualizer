#pragma once
#ifndef BFSVISUALIZER_H
#define BFSVISUALIZER_H

#include <SFML/Graphics.hpp>
#include <vector>

// Function to calculate heuristic (not essential for BFS but follows A* structure)
float heuristicBFS(const sf::Vector2i& a, const sf::Vector2i& b);

// Convert 2D grid position to a 1D index for storage in maps or arrays
int toIndexBFS(const sf::Vector2i& pos, int gridWidth);

// Get valid neighbors of a grid cell
std::vector<sf::Vector2i> getNeighborsBFS(const sf::Vector2i& pos);

 //BFS function that performs visualization and returns the shortest path
std::vector<sf::Vector2i> bfsVisualized(
    const sf::Vector2i& start,
    const sf::Vector2i& goal,
    const std::vector<std::vector<int>>& hurdleMatrix,
    sf::RenderWindow& window,
    int tileSize,
     int& totalExpandedNodes,
     bool& pathFound
);

// Function to run BFS visualization (setup and event handling)
void runBFSVisualizer();

#endif // BFSVISUALIZER_H
