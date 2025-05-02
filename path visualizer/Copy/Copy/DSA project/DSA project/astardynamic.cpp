#include "astardynamic.h"
#include <cmath>
#include <iostream>
#include <thread>
#include <chrono>

//float NodeS::getFCost() const {
//    return gCost + hCost;
//}
//
//bool NodeS::operator<(const NodeS& other) const {
//    return getFCost() > other.getFCost();
//}

float heuristic(const sf::Vector2i& a, const sf::Vector2i& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

int toIndex(const sf::Vector2i& pos, int gridWidth) {
    return pos.y * gridWidth + pos.x;
}

std::vector<sf::Vector2i> getNeighbors(const sf::Vector2i& pos) {
    return {
        {pos.x + 1, pos.y},
        {pos.x - 1, pos.y},
        {pos.x, pos.y + 1},
        {pos.x, pos.y - 1}
    };
}

std::vector<sf::Vector2i> aStarVisualized(
    const sf::Vector2i& start,
    const sf::Vector2i& goal,
    const std::vector<std::vector<int>>& hurdleMatrix,
    sf::RenderWindow& window,
    int tileSize,
    int& totalExpandedNodes) {

    const int gridWidth = hurdleMatrix[0].size();
    const int gridHeight = hurdleMatrix.size();

    std::priority_queue<NodeS> openSet;
    std::unordered_map<int, NodeS> allNodes;
    std::unordered_map<int, bool> closedSet;

    NodeS startNode{ start };
    allNodes[toIndex(start, gridWidth)] = startNode;
    openSet.push(startNode);

    std::vector<sf::Vector2i> openNodes;
    std::vector<sf::Vector2i> closedNodes;

    totalExpandedNodes = 0; // Initialize expanded nodes counter

    while (!openSet.empty()) {
        NodeS current = openSet.top();
        openSet.pop();
        closedSet[toIndex(current.position, gridWidth)] = true;
        closedNodes.push_back(current.position);
        totalExpandedNodes++;

        // Check if we reached the goal
        if (current.position == goal) {
            std::vector<sf::Vector2i> path;
            NodeS* pathNode = &allNodes[toIndex(current.position, gridWidth)];
            while (pathNode) {
                path.push_back(pathNode->position);
                pathNode = pathNode->parent;
            }
            std::reverse(path.begin(), path.end());

            // Display the final path
            for (const auto& pos : path) {
                sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
                cell.setPosition(pos.x * tileSize, pos.y * tileSize);
                cell.setFillColor(sf::Color::Green);
                window.draw(cell);
            }

            window.display();
            return path;
        }

        for (const auto& neighborPos : getNeighbors(current.position)) {
            if (neighborPos.x < 0 || neighborPos.y < 0 ||
                neighborPos.x >= gridWidth || neighborPos.y >= gridHeight ||
                hurdleMatrix[neighborPos.y][neighborPos.x] == 1) {
                continue;
            }

            int neighborIndex = toIndex(neighborPos, gridWidth);
            if (closedSet.find(neighborIndex) != closedSet.end()) continue;

            float newGCost = current.gCost + 1;

            if (allNodes.find(neighborIndex) == allNodes.end() || newGCost < allNodes[neighborIndex].gCost) {
                NodeS neighborNode{ neighborPos };
                neighborNode.gCost = newGCost;
                neighborNode.hCost = heuristic(neighborPos, goal);
                neighborNode.parent = &allNodes[toIndex(current.position, gridWidth)];
                allNodes[neighborIndex] = neighborNode;
                openSet.push(neighborNode);
                openNodes.push_back(neighborPos);
            }
        }

        // Render the grid with explored nodes during the search
        window.clear();

        for (int y = 0; y < gridHeight; ++y) {
            for (int x = 0; x < gridWidth; ++x) {
                sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
                cell.setPosition(x * tileSize, y * tileSize);
                if (hurdleMatrix[y][x] == 1) {
                    cell.setFillColor(sf::Color::Black);
                }
                else {
                    cell.setFillColor(sf::Color::White);
                }
                window.draw(cell);
            }
        }

        for (const auto& pos : closedNodes) {
            sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
            cell.setPosition(pos.x * tileSize, pos.y * tileSize);
            cell.setFillColor(sf::Color::Cyan);
            window.draw(cell);
        }

        for (const auto& pos : openNodes) {
            sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
            cell.setPosition(pos.x * tileSize, pos.y * tileSize);
            cell.setFillColor(sf::Color::Yellow);
            window.draw(cell);
        }

        sf::RectangleShape startCell(sf::Vector2f(tileSize - 1, tileSize - 1));
        startCell.setPosition(start.x * tileSize, start.y * tileSize);
        startCell.setFillColor(sf::Color::Blue);
        window.draw(startCell);

        sf::RectangleShape goalCell(sf::Vector2f(tileSize - 1, tileSize - 1));
        goalCell.setPosition(goal.x * tileSize, goal.y * tileSize);
        goalCell.setFillColor(sf::Color::Red);
        window.draw(goalCell);

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    return {}; // Return an empty path if no path is found
}

void runAStarVisualizer() {
    const int gridWidth = 25;
    const int gridHeight = 25;
    const int tileSize = 20;

    sf::RenderWindow window(sf::VideoMode(gridWidth * tileSize, gridHeight * tileSize), "A* Pathfinding Visualization");

    std::vector<std::vector<int>> hurdleMatrix(gridHeight, std::vector<int>(gridWidth, 0));

    sf::Vector2i start(0, 0);
    sf::Vector2i goal(gridWidth - 1, gridHeight - 1);

    std::vector<sf::Vector2i> path;
    int totalExpandedNodes = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int x = mousePos.x / tileSize;
                int y = mousePos.y / tileSize;
                if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                    hurdleMatrix[y][x] = 1;
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                path = aStarVisualized(start, goal, hurdleMatrix, window, tileSize, totalExpandedNodes);
            }
        }
    }

    // After visualization, display total expanded nodes and final path
    std::cout << "Total Expanded Nodes: " << totalExpandedNodes << std::endl;
}

