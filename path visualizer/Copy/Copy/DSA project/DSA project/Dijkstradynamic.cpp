#include <queue>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "dijkstradynamic.h"


float heuristicDijkstra(const sf::Vector2i& a, const sf::Vector2i& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

int toIndexDijkstra(const sf::Vector2i& pos, int gridWidth) {
    return pos.y * gridWidth + pos.x;
}

std::vector<sf::Vector2i> getNeighborsDijkstra(const sf::Vector2i& pos) {
    return {
        {pos.x + 1, pos.y},
        {pos.x - 1, pos.y},
        {pos.x, pos.y + 1},
        {pos.x, pos.y - 1}
    };
}
std::vector<sf::Vector2i> dijkstraVisualized(
	    const sf::Vector2i& start,
	    const sf::Vector2i& goal,
	    const std::vector<std::vector<int>>& hurdleMatrix,
	    sf::RenderWindow& window,
	    int tileSize) {
	
	    const int gridWidth = hurdleMatrix[0].size();
	    const int gridHeight = hurdleMatrix.size();
	
	    std::priority_queue<NodeE, std::vector<NodeE>, std::greater<NodeE>> openQueue;
	    std::unordered_map<int, NodeE> allNodes;
	    std::unordered_map<int, bool> visited;
	
	    NodeE startNode(start);
	    startNode.gCost = 0.0f;
	    allNodes[toIndexDijkstra(start, gridWidth)] = startNode;
	    openQueue.push(startNode);
	
	    std::vector<sf::Vector2i> visitedNodes;
	
	    while (!openQueue.empty()) {
	        NodeE current = openQueue.top();
	        openQueue.pop();
	        visited[toIndexDijkstra(current.position, gridWidth)] = true;
	        visitedNodes.push_back(current.position);
	
	        if (current.position == goal) {
	            std::vector<sf::Vector2i> path;
	            NodeE* pathNode = &allNodes[toIndexDijkstra(current.position, gridWidth)];
	            while (pathNode) {
	                path.push_back(pathNode->position);
	                pathNode = pathNode->parent;
	            }
	            std::reverse(path.begin(), path.end());
	            return path;
	        }
	
	        for (const auto& neighborPos : getNeighborsDijkstra(current.position)) {
	            if (neighborPos.x < 0 || neighborPos.y < 0 ||
	                neighborPos.x >= gridWidth || neighborPos.y >= gridHeight ||
	                hurdleMatrix[neighborPos.y][neighborPos.x] == 1) {
	                continue;
	            }
	
	            int neighborIndex = toIndexDijkstra(neighborPos, gridWidth);
	            float newGCost = current.gCost + 1.0f;
	
	            if (allNodes.find(neighborIndex) == allNodes.end() || newGCost < allNodes[neighborIndex].gCost) {
	                NodeE neighborNode(neighborPos);
	                neighborNode.gCost = newGCost;
	                neighborNode.parent = &allNodes[toIndexDijkstra(current.position, gridWidth)];
	                allNodes[neighborIndex] = neighborNode;
	                openQueue.push(neighborNode);
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

	void runDijkstraVisualizer() {
	    const int gridWidth = 25;
	    const int gridHeight = 25;
	    const int tileSize = 20;
	
	    sf::RenderWindow window(sf::VideoMode(gridWidth * tileSize, gridHeight * tileSize), "Dijkstra Pathfinding Visualization");
	
	    std::vector<std::vector<int>> hurdleMatrix(gridHeight, std::vector<int>(gridWidth, 0));
	
	    sf::Vector2i start(0, 0);
	    sf::Vector2i goal(gridWidth - 1, gridHeight - 1);
	
	    std::vector<sf::Vector2i> path;
	
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
	
	            // Start Dijkstra visualization
	            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
	                path = dijkstraVisualized(start, goal, hurdleMatrix, window, tileSize);
	            }
	        }
	    }
	}



