#ifndef DFSDYNAMIC_H
#define DFSDYNAMIC_H

#include <SFML/Graphics.hpp>
#include <vector>

float heuristicDFS(const sf::Vector2i& a, const sf::Vector2i& b);
int toIndexDFS(const sf::Vector2i& pos, int gridWidth);
std::vector<sf::Vector2i> getNeighborsDFS(const sf::Vector2i& pos);

std::vector<sf::Vector2i> dfsVisualized(
    const sf::Vector2i& start,
    const sf::Vector2i& goal,
    const std::vector<std::vector<int>>& hurdleMatrix,
    sf::RenderWindow& window,
    int tileSize,
    int& totalExpandedNodes,
    bool& pathFound
);

void runDFSVisualizer();

#endif // DFSDYNAMIC_H
