#include "pathfinding.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include <algorithm>

void visualizePathfinding(
    const std::vector<std::vector<Node>>& maze,
    const PathfindingAlgorithm& algorithm,
    const sf::Vector2i& start,
    const sf::Vector2i& end
) {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width;
    unsigned int windowHeight = desktopMode.height;

    int rows = static_cast<int>(maze.size());
    int cols = static_cast<int>(maze[0].size());
    float scaleX = static_cast<float>(windowWidth) / cols;
    float scaleY = static_cast<float>(windowHeight) / rows;
    float cellSize = std::min(scaleX, scaleY);

    sf::RenderWindow window(
        sf::VideoMode(windowWidth, windowHeight),
        "Pathfinding Visualizer",
        sf::Style::Default
    );

    sf::RectangleShape cellShape(sf::Vector2f(cellSize - 1, cellSize - 1));

    // Visualization callback
    auto visualizeStep = [&](const std::vector<std::vector<Node>>& grid) {
        window.clear(sf::Color::Black);

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                if (grid[y][x].isHurdle)
                    cellShape.setFillColor(sf::Color::Black);
                else if (grid[y][x].isVisited)
                    cellShape.setFillColor(sf::Color::Cyan);
                else
                    cellShape.setFillColor(sf::Color::White);

                cellShape.setPosition(x * cellSize, y * cellSize);
                window.draw(cellShape);
            }
        }

        window.display();
        sf::sleep(sf::milliseconds(25)); // Animation delay
        };

    // Run the algorithm with the visualization callback
    std::vector<sf::Vector2i> path = algorithm(maze, start, end, visualizeStep);

    // Draw the final path
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                if (maze[y][x].isHurdle)
                    cellShape.setFillColor(sf::Color::Black);
                else if (maze[y][x].isVisited)
                    cellShape.setFillColor(sf::Color::Cyan);
                else
                    cellShape.setFillColor(sf::Color::White);

                cellShape.setPosition(x * cellSize, y * cellSize);
                window.draw(cellShape);
            }
        }

        for (const sf::Vector2i& pos : path) {
            cellShape.setFillColor(sf::Color::Blue);
            cellShape.setPosition(pos.x * cellSize, pos.y * cellSize);
            window.draw(cellShape);
        }

        cellShape.setFillColor(sf::Color::Green);
        cellShape.setPosition(start.x * cellSize, start.y * cellSize);
        window.draw(cellShape);

        cellShape.setFillColor(sf::Color::Yellow);
        cellShape.setPosition(end.x * cellSize, end.y * cellSize);
        window.draw(cellShape);

        window.display();
    }
}
