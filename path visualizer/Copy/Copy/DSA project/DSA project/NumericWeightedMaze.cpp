#include "NumericWeightedMaze.h"
#include "Node.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>




void createNumericWeightedMaze(const PathfindingAlgorithm& algorithm) {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width-200;
    unsigned int windowHeight = desktopMode.height - 200;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Numeric Weighted Maze", sf::Style::Default);
    window.setPosition(sf::Vector2i((desktopMode.width - windowWidth) / 4, (desktopMode.height - windowHeight) / 4));

    int cellSize = 60;
    int rows = (windowHeight / cellSize) - 1;
    int cols = windowWidth / cellSize;

    std::vector<std::vector<Node>> grid(rows, std::vector<Node>(cols));

    // Initialize the grid with basic node setup
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            grid[y][x].x = x;
            grid[y][x].y = y;
            grid[y][x].position = std::make_pair(x, y);
        }
    }

    // Randomly assign weights
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if ((rand() % 100) < 60) { // 40-60% chance of having a weight
                grid[y][x].hasWeight = true;
                grid[y][x].weight = 1 + (rand() % 10);
            }
        }
    }

    // Ensure start and end nodes don't have weights
    grid[0][0].hasWeight = false;
    grid[0][0].weight = 1;
    grid[rows - 1][cols - 1].hasWeight = false;
    grid[rows - 1][cols - 1].weight = 1;

    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    auto visualizeStep = [&](const std::vector<std::vector<Node>>& currentGrid) {
        window.clear(sf::Color::Black);
        sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                const Node& node = currentGrid[y][x];

                // Color coding based on node state
                if (x == 0 && y == 0)
                    cell.setFillColor(sf::Color::Green);
                else if (x == cols - 1 && y == rows - 1)
                    cell.setFillColor(sf::Color::Yellow);
                else if (node.isVisited)
                    cell.setFillColor(sf::Color::Cyan);
                else
                    cell.setFillColor(sf::Color::White);

                cell.setPosition(x * cellSize, y * cellSize);
                window.draw(cell);

                // Draw weight
                if (node.hasWeight) {
                    sf::Text weightText;
                    weightText.setFont(font);
                    weightText.setString(std::to_string(node.weight));
                    weightText.setCharacterSize(20);
                    weightText.setFillColor(sf::Color::Magenta);

                    // Center the text
                    float textX = (x * cellSize) + (cellSize - weightText.getLocalBounds().width) / 2;
                    float textY = (y * cellSize) + (cellSize - weightText.getLocalBounds().height) / 2;
                    weightText.setPosition(textX, textY);

                    window.draw(weightText);
                }
            }
        }

        window.display();
        sf::sleep(sf::milliseconds(20));
        };

    // Execute the algorithm
    std::vector<sf::Vector2i> path = algorithm(grid, { 0, 0 }, { cols - 1, rows - 1 }, visualizeStep);

    // Final visualization loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));

        // Draw base grid
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                const Node& node = grid[y][x];

                if (x == 0 && y == 0)
                    cell.setFillColor(sf::Color::Green);
                else if (x == cols - 1 && y == rows - 1)
                    cell.setFillColor(sf::Color::Yellow);
                else if (node.isVisited)
                    cell.setFillColor(sf::Color::Cyan);
                else
                    cell.setFillColor(sf::Color::White);

                cell.setPosition(x * cellSize, y * cellSize);
                window.draw(cell);

                if (node.hasWeight) {
                    sf::Text weightText;
                    weightText.setFont(font);
                    weightText.setString(std::to_string(node.weight));
                    weightText.setCharacterSize(20);
                    weightText.setFillColor(sf::Color::Magenta);
                    float textX = (x * cellSize) + (cellSize - weightText.getLocalBounds().width) / 2;
                    float textY = (y * cellSize) + (cellSize - weightText.getLocalBounds().height) / 2;
                    weightText.setPosition(textX, textY);
                    window.draw(weightText);
                }
            }
        }

        // Draw path
        if (!path.empty()) {
            for (const auto& pos : path) {
                cell.setFillColor(sf::Color(0, 0, 255, 180));  // Semi-transparent blue
                cell.setPosition(pos.x * cellSize, pos.y * cellSize);
                window.draw(cell);
            }
        }

        window.display();
    }
}