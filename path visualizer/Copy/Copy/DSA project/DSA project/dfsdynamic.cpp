#include <stack>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "dfsdynamic.h"

float heuristicDFS(const sf::Vector2i& a, const sf::Vector2i& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

int toIndexDFS(const sf::Vector2i& pos, int gridWidth) {
    return pos.y * gridWidth + pos.x;
}

std::vector<sf::Vector2i> getNeighborsDFS(const sf::Vector2i& pos) {
    return {
        {pos.x + 1, pos.y},
        {pos.x - 1, pos.y},
        {pos.x, pos.y + 1},
        {pos.x, pos.y - 1}
    };
}

std::vector<sf::Vector2i> dfsVisualized(
    const sf::Vector2i& start,
    const sf::Vector2i& goal,
    const std::vector<std::vector<int>>& hurdleMatrix,
    sf::RenderWindow& window,
    int tileSize,
    int& totalExpandedNodes,
    bool& pathFound) {

    const int gridWidth = hurdleMatrix[0].size();
    const int gridHeight = hurdleMatrix.size();

    std::stack<sf::Vector2i> openStack;
    std::unordered_map<int, sf::Vector2i> parentMap;
    std::unordered_map<int, bool> visited;

    openStack.push(start);
    visited[toIndexDFS(start, gridWidth)] = true;

    std::vector<sf::Vector2i> visitedNodes;
    totalExpandedNodes = 0;
    pathFound = false;

    while (!openStack.empty()) {
        sf::Vector2i current = openStack.top();
        openStack.pop();
        visitedNodes.push_back(current);
        totalExpandedNodes++;

        if (current == goal) {
            pathFound = true;
            std::vector<sf::Vector2i> path;
            for (sf::Vector2i at = goal; at != start; at = parentMap[toIndexDFS(at, gridWidth)]) {
                path.push_back(at);
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& neighbor : getNeighborsDFS(current)) {
            if (neighbor.x < 0 || neighbor.y < 0 ||
                neighbor.x >= gridWidth || neighbor.y >= gridHeight ||
                hurdleMatrix[neighbor.y][neighbor.x] == 1) {
                continue;
            }

            int neighborIndex = toIndexDFS(neighbor, gridWidth);
            if (!visited[neighborIndex]) {
                openStack.push(neighbor);
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

    return {};
}

void runDFSVisualizer() {
    const int gridWidth = 25;
    const int gridHeight = 25;
    const int tileSize = 20;

    sf::RenderWindow window(sf::VideoMode(gridWidth * tileSize, gridHeight * tileSize), "DFS Pathfinding Visualization");

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

            // Start DFS visualization
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                path = dfsVisualized(start, goal, hurdleMatrix, window, tileSize, totalExpandedNodes, pathFound);

                // Print results to console
                std::cout << "Total Nodes Expanded: " << totalExpandedNodes << "\n";
                std::cout << (pathFound ? "Path Found" : "No Path Found") << "\n";
            }
        }
    }
}

