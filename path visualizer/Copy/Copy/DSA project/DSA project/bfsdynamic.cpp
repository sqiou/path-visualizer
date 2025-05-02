//#include <queue>
//#include <unordered_map>
//#include <vector>
//#include <cmath>
//#include <thread>
//#include <chrono>
//#include <SFML/Graphics.hpp>
//#include "bfsdynamic.h"
//
//float heuristicBFS(const sf::Vector2i& a, const sf::Vector2i& b) {
//    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
//}
//
//int toIndexBFS(const sf::Vector2i& pos, int gridWidth) {
//    return pos.y * gridWidth + pos.x;
//}
//
//std::vector<sf::Vector2i> getNeighborsBFS(const sf::Vector2i& pos) {
//    return {
//        {pos.x + 1, pos.y},
//        {pos.x - 1, pos.y},
//        {pos.x, pos.y + 1},
//        {pos.x, pos.y - 1}
//    };
//}
//
//
//    const int gridWidth = hurdleMatrix[0].size();
//    const int gridHeight = hurdleMatrix.size();
//
//    std::queue<sf::Vector2i> openQueue;
//    std::unordered_map<int, sf::Vector2i> parentMap;
//    std::unordered_map<int, bool> visited;
//
//    openQueue.push(start);
//    visited[toIndexBFS(start, gridWidth)] = true;
//
//    std::vector<sf::Vector2i> visitedNodes;
//
//    while (!openQueue.empty()) {
//        sf::Vector2i current = openQueue.front();
//        openQueue.pop();
//        visitedNodes.push_back(current);
//
//        if (current == goal) {
//            std::vector<sf::Vector2i> path;
//            for (sf::Vector2i at = goal; at != start; at = parentMap[toIndexBFS(at, gridWidth)]) {
//                path.push_back(at);
//            }
//            path.push_back(start);
//            std::reverse(path.begin(), path.end());
//            return path;
//        }
//
//        for (const auto& neighbor : getNeighborsBFS(current)) {
//            if (neighbor.x < 0 || neighbor.y < 0 ||
//                neighbor.x >= gridWidth || neighbor.y >= gridHeight ||
//                hurdleMatrix[neighbor.y][neighbor.x] == 1) {
//                continue;
//            }
//
//            int neighborIndex = toIndexBFS(neighbor, gridWidth);
//            if (!visited[neighborIndex]) {
//                openQueue.push(neighbor);
//                visited[neighborIndex] = true;
//                parentMap[neighborIndex] = current;
//            }
//        }
//
//        // Visualization
//        window.clear();
//
//        // Draw the grid
//        for (int y = 0; y < gridHeight; ++y) {
//            for (int x = 0; x < gridWidth; ++x) {
//                sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
//                cell.setPosition(x * tileSize, y * tileSize);
//                if (hurdleMatrix[y][x] == 1) {
//                    cell.setFillColor(sf::Color::Black); // Hurdles
//                }
//                else {
//                    cell.setFillColor(sf::Color::White); // Empty space
//                }
//                window.draw(cell);
//            }
//        }
//
//        // Draw visited nodes
//        for (const auto& pos : visitedNodes) {
//            sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
//            cell.setPosition(pos.x * tileSize, pos.y * tileSize);
//            cell.setFillColor(sf::Color::Cyan); // Visited
//            window.draw(cell);
//        }
//
//        // Draw start and goal
//        sf::RectangleShape startCell(sf::Vector2f(tileSize - 1, tileSize - 1));
//        startCell.setPosition(start.x * tileSize, start.y * tileSize);
//        startCell.setFillColor(sf::Color::Blue); // Start
//        window.draw(startCell);
//
//        sf::RectangleShape goalCell(sf::Vector2f(tileSize - 1, tileSize - 1));
//        goalCell.setPosition(goal.x * tileSize, goal.y * tileSize);
//        goalCell.setFillColor(sf::Color::Red); // Goal
//        window.draw(goalCell);
//
//        window.display();
//        std::this_thread::sleep_for(std::chrono::milliseconds(20));
//    }
//
//    return {};
//}
//
//void runBFSVisualizer() {
//    const int gridWidth = 25;
//    const int gridHeight = 25;
//    const int tileSize = 20;
//
//    sf::RenderWindow window(sf::VideoMode(gridWidth * tileSize, gridHeight * tileSize), "BFS Pathfinding Visualization");
//
//    std::vector<std::vector<int>> hurdleMatrix(gridHeight, std::vector<int>(gridWidth, 0));
//
//    sf::Vector2i start(0, 0);
//    sf::Vector2i goal(gridWidth - 1, gridHeight - 1);
//
//    std::vector<sf::Vector2i> path;
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//
//            // Add hurdles dynamically
//            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//                int x = mousePos.x / tileSize;
//                int y = mousePos.y / tileSize;
//                if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
//                    hurdleMatrix[y][x] = 1; // Add hurdle
//                }
//            }
//
//            // Clear hurdles
//            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
//                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//                int x = mousePos.x / tileSize;
//                int y = mousePos.y / tileSize;
//                if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
//                    hurdleMatrix[y][x] = 0; // Remove hurdle
//                }
//            }
//
//            // Start BFS visualization
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
//                path = bfsVisualized(start, goal, hurdleMatrix, window, tileSize);
//            }
//        }
//    }


#include <queue>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "bfsdynamic.h"

float heuristicBFS(const sf::Vector2i& a, const sf::Vector2i& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

int toIndexBFS(const sf::Vector2i& pos, int gridWidth) {
    return pos.y * gridWidth + pos.x;
}

std::vector<sf::Vector2i> getNeighborsBFS(const sf::Vector2i& pos) {
    return {
        {pos.x + 1, pos.y},
        {pos.x - 1, pos.y},
        {pos.x, pos.y + 1},
        {pos.x, pos.y - 1}
    };
}

std::vector<sf::Vector2i> bfsVisualized(
    const sf::Vector2i& start,
    const sf::Vector2i& goal,
    const std::vector<std::vector<int>>& hurdleMatrix,
    sf::RenderWindow& window,
    int tileSize,
    int& totalExpandedNodes, // Add total expanded nodes as reference
    bool& pathFound          // Add path found as reference
) {
    const int gridWidth = hurdleMatrix[0].size();
    const int gridHeight = hurdleMatrix.size();

    std::queue<sf::Vector2i> openQueue;
    std::unordered_map<int, sf::Vector2i> parentMap;
    std::unordered_map<int, bool> visited;

    openQueue.push(start);
    visited[toIndexBFS(start, gridWidth)] = true;

    std::vector<sf::Vector2i> visitedNodes;
    totalExpandedNodes = 0; // Initialize expanded nodes counter
    pathFound = false;      // Initialize path found flag

    while (!openQueue.empty()) {
        sf::Vector2i current = openQueue.front();
        openQueue.pop();
        visitedNodes.push_back(current);
        totalExpandedNodes++; // Increment expanded nodes

        if (current == goal) {
            pathFound = true; // Path is found
            std::vector<sf::Vector2i> path;
            for (sf::Vector2i at = goal; at != start; at = parentMap[toIndexBFS(at, gridWidth)]) {
                path.push_back(at);
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& neighbor : getNeighborsBFS(current)) {
            if (neighbor.x < 0 || neighbor.y < 0 ||
                neighbor.x >= gridWidth || neighbor.y >= gridHeight ||
                hurdleMatrix[neighbor.y][neighbor.x] == 1) {
                continue;
            }

            int neighborIndex = toIndexBFS(neighbor, gridWidth);
            if (!visited[neighborIndex]) {
                openQueue.push(neighbor);
                visited[neighborIndex] = true;
                parentMap[neighborIndex] = current;
            }
        }

        // Visualization
        window.clear();

        // Draw the grid
        for (int y = 0; y < gridHeight; ++y) {
            for (int x = 0; x < gridWidth; ++x) {
                sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
                cell.setPosition(x * tileSize, y * tileSize);
                if (hurdleMatrix[y][x] == 1) {
                    cell.setFillColor(sf::Color::Black); // Hurdles
                }
                else {
                    cell.setFillColor(sf::Color::White); // Empty space
                }
                window.draw(cell);
            }
        }

        // Draw visited nodes
        for (const auto& pos : visitedNodes) {
            sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
            cell.setPosition(pos.x * tileSize, pos.y * tileSize);
            cell.setFillColor(sf::Color::Cyan); // Visited
            window.draw(cell);
        }

        // Draw start and goal
        sf::RectangleShape startCell(sf::Vector2f(tileSize - 1, tileSize - 1));
        startCell.setPosition(start.x * tileSize, start.y * tileSize);
        startCell.setFillColor(sf::Color::Blue); // Start
        window.draw(startCell);

        sf::RectangleShape goalCell(sf::Vector2f(tileSize - 1, tileSize - 1));
        goalCell.setPosition(goal.x * tileSize, goal.y * tileSize);
        goalCell.setFillColor(sf::Color::Red); // Goal
        window.draw(goalCell);

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    return {}; // Return empty path if no path is found
}


void runBFSVisualizer() {
    const int gridWidth = 25;
    const int gridHeight = 25;
    const int tileSize = 20;

    sf::RenderWindow window(sf::VideoMode(gridWidth * tileSize, gridHeight * tileSize), "BFS Pathfinding Visualization");

    std::vector<std::vector<int>> hurdleMatrix(gridHeight, std::vector<int>(gridWidth, 0));

    sf::Vector2i start(0, 0);
    sf::Vector2i goal(gridWidth - 1, gridHeight - 1);

    std::vector<sf::Vector2i> path;
    int totalExpandedNodes = 0;
    bool pathFound = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Add hurdles dynamically
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int x = mousePos.x / tileSize;
                int y = mousePos.y / tileSize;
                if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                    hurdleMatrix[y][x] = 1; // Add hurdle
                }
            }

            // Clear hurdles
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int x = mousePos.x / tileSize;
                int y = mousePos.y / tileSize;
                if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                    hurdleMatrix[y][x] = 0; // Remove hurdle
                }
            }

            // Start BFS visualization
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                path = bfsVisualized(start, goal, hurdleMatrix, window, tileSize, totalExpandedNodes, pathFound);

                if (pathFound) {
                    std::cout << "Path found! Total nodes expanded: " << totalExpandedNodes << "\n";
                    std::cout << "Path length: " << path.size() << "\n";
                }
                else {
                    std::cout << "No path found. Total nodes expanded: " << totalExpandedNodes << "\n";
                }
            }
        }
    }
}
