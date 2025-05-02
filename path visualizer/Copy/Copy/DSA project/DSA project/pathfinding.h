#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "bfs.h"

using PathfindingAlgorithm = std::function<std::vector<sf::Vector2i>(
    const std::vector<std::vector<Node>>&,
    const sf::Vector2i&,
    const sf::Vector2i&,
    std::function<void(const std::vector<std::vector<Node>>&)> visualizeStep)>;

//using PathfindingAlgorithm = std::function<void(
//    std::vector<std::vector<Node>>&, Node&, Node&,
//    std::function<void(const std::vector<std::vector<Node>>&)>
//    )>;

void visualizePathfinding(
    const std::vector<std::vector<Node>>& maze,
    const PathfindingAlgorithm& algorithm,
    const sf::Vector2i& start,
    const sf::Vector2i& end);

