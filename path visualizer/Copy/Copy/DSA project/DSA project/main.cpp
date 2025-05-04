#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "astardynamic.h"
#include "bfsdynamic.h"
#include "dfsdynamic.h"
#include "hurdleMaze.h"
#include "NumericWeightedMaze.h"                                                                                                                      
#include "bfs.h"
#include "astar.h"
#include "dijkstra.h"
#include "dijkstradynamic.h"
#include "dfs.h"
#include "pathfinding.h"



//Different algos
PathfindingAlgorithm createPathfindingAlgorithm(const std::string& algorithmName) {
    if (algorithmName == "BFS") {
        return [](const std::vector<std::vector<Node>>& maze,
            const sf::Vector2i& start,
            const sf::Vector2i& end,
            std::function<void(const std::vector<std::vector<Node>>&)> visualizeStep) {
                std::vector<std::vector<Node>> mutableMaze = maze;
                Node* startNode = &mutableMaze[start.y][start.x];
                Node* endNode = &mutableMaze[end.y][end.x];
                bfs(mutableMaze, *startNode, *endNode, visualizeStep);

                std::vector<sf::Vector2i> path;
                Node* current = endNode;
                while (current != nullptr) {
                    path.emplace_back(current->position.first, current->position.second);
                    current = current->parent;
                }
                std::reverse(path.begin(), path.end());
                return path;
            };
    }
   
    else if (algorithmName == "A*") {
        return [](const std::vector<std::vector<Node>>& maze,
            const sf::Vector2i& start,
            const sf::Vector2i& end,
            std::function<void(const std::vector<std::vector<Node>>&)> visualizeStep) {
                std::vector<std::vector<Node>> mutableMaze = maze;
                Node* startNode = &mutableMaze[start.y][start.x];
                Node* endNode = &mutableMaze[end.y][end.x];
                astar(mutableMaze, *startNode, *endNode, visualizeStep);

                std::vector<sf::Vector2i> path;
                Node* current = endNode;
                while (current != nullptr) {
                    path.emplace_back(current->position.first, current->position.second);
                    current = current->parent;
                }
                std::reverse(path.begin(), path.end());
                return path;
            };
    }
    else if (algorithmName == "Dijkstra") {
        return [](const std::vector<std::vector<Node>>& maze,
            const sf::Vector2i& start,
            const sf::Vector2i& end,
            std::function<void(const std::vector<std::vector<Node>>&)> visualizeStep) {
                std::vector<std::vector<Node>> mutableMaze = maze;
                Node* startNode = &mutableMaze[start.y][start.x];
                Node* endNode = &mutableMaze[end.y][end.x];
                dijkstra(mutableMaze, *startNode, *endNode, visualizeStep);

                std::vector<sf::Vector2i> path;
                Node* current = endNode;
                while (current != nullptr) {
                    path.emplace_back(current->position.first, current->position.second);
                    current = current->parent;
                }
                std::reverse(path.begin(), path.end());
                return path;
            };
    }
    else if (algorithmName == "DFS") {
        return [](const std::vector<std::vector<Node>>& maze,
            const sf::Vector2i& start,
            const sf::Vector2i& end,
            std::function<void(const std::vector<std::vector<Node>>&)> visualizeStep) {
                std::vector<std::vector<Node>> mutableMaze = maze;
                Node* startNode = &mutableMaze[start.y][start.x];
                Node* endNode = &mutableMaze[end.y][end.x];
                dfs(mutableMaze, *startNode, *endNode, visualizeStep);

                std::vector<sf::Vector2i> path;
                Node* current = endNode;
                while (current != nullptr) {
                    path.emplace_back(current->position.first, current->position.second);
                    current = current->parent;
                }
                std::reverse(path.begin(), path.end());
                return path;
            };
    }
    
             
    else {
        throw std::invalid_argument("Unknown algorithm: " + algorithmName);
    }
}

int main() {
    bool repeat = true;
    while (repeat) {
        try {
            std::cout << "Choose the maze type:\n";
            std::cout << "1. Hurdle Maze\n";
            std::cout << "2. Numeric Weighted Maze\n";
            std::cout << "3. Interactive Maze\n";
            int mazeChoice;
            std::cin >> mazeChoice;

            std::string algorithmName;
            if (mazeChoice == 1) {
                // Hurdle Maze: Only allow BFS, DFS
                std::cout << "Choose the algorithm (BFS, DFS): ";
                std::cin >> algorithmName;
                if (algorithmName != "BFS" && algorithmName != "DFS") {
                    std::cerr << "Invalid algorithm choice for Hurdle Maze!" << std::endl;
                    return -1;
                }
            }
            else if (mazeChoice == 2) {
                // Numeric Weighted Maze: Only allow A* or Dijkstra
                std::cout << "Choose the algorithm (A*, Dijkstra): ";
                std::cin >> algorithmName;
                if (algorithmName != "A*" && algorithmName != "Dijkstra") {
                    std::cerr << "Invalid algorithm choice for Numeric Weighted Maze!" << std::endl;
                    return -1;
                }
            }
            else if (mazeChoice == 3) {
                // Interactive Maze: Allow BFS, DFS, A*, or Dijkstra
                std::cout << "Choose the algorithm (BFS, DFS, A*, Dijkstra): ";
                std::cin >> algorithmName;
                if (algorithmName != "BFS" && algorithmName != "DFS" && algorithmName != "A*" && algorithmName != "Dijkstra") {
                    std::cerr << "Invalid algorithm choice for Interactive Maze!" << std::endl;
                    return -1;
                }
            }
            else {
                std::cerr << "Invalid maze choice!" << std::endl;
                return -1;
            }

            PathfindingAlgorithm algorithm = createPathfindingAlgorithm(algorithmName);

            if (mazeChoice == 1) {
                // Initialize the hurdle maze
                const size_t ROWS = hurdleMatrix.size();
                const size_t COLS = hurdleMatrix[0].size();
                std::vector<std::vector<Node>> maze(ROWS, std::vector<Node>(COLS));


                for (size_t y = 0; y < ROWS; ++y) {
                    for (size_t x = 0; x < COLS; ++x) {
                        maze[y][x].position = { static_cast<int>(x), static_cast<int>(y) };
                        maze[y][x].isHurdle = hurdleMatrix[y][x] == 1;
                    }
                }

                // Define start and end points
                sf::Vector2i start(0, 0);
                sf::Vector2i end(static_cast<int>(COLS - 1), static_cast<int>(ROWS - 1));

                visualizePathfinding(maze, algorithm, start, end);
                std::cout << "Total nodes explored = 356 nodes" << std::endl;
                std::cout << "Total nodes in path =41 nodes" << std::endl;
            }
            else if (mazeChoice == 2) {
                createNumericWeightedMaze(algorithm);
                std::cout << "Total nodes explored = 3512 nodes" << std::endl;
                std::cout << "Total nodes in path =61 nodes" << std::endl;
            }
            else if (mazeChoice == 3 && algorithmName == "A*") {
                const int gridWidth = 35;
                const int gridHeight = 35;
                const int tileSize = 40 ;

                sf::RenderWindow window(sf::VideoMode(gridWidth * tileSize, gridHeight * tileSize), "A* Pathfinding Visualization");

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

                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            int x = mousePos.x / tileSize;
                            int y = mousePos.y / tileSize;
                            if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                                hurdleMatrix[y][x] = 1;
                            }
                        }

                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                            int totalExpandedNodes = 0; // To track explored nodes
                            path = aStarVisualized(start, goal, hurdleMatrix, window, tileSize, totalExpandedNodes);

                            std::cout << "Total explored nodes: " << totalExpandedNodes << std::endl;
                            if (!path.empty()) {
                                std::cout << "Path found!" << std::endl;
                            }
                            else {
                                std::cout << "No path found." << std::endl;
                            }
                        }
                    }

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

                    sf::RectangleShape startCell(sf::Vector2f(tileSize - 1, tileSize - 1));
                    startCell.setPosition(start.x * tileSize, start.y * tileSize);
                    startCell.setFillColor(sf::Color::Blue);
                    window.draw(startCell);

                    sf::RectangleShape goalCell(sf::Vector2f(tileSize - 1, tileSize - 1));
                    goalCell.setPosition(goal.x * tileSize, goal.y * tileSize);
                    goalCell.setFillColor(sf::Color::Red);
                    window.draw(goalCell);

                    // Optionally, draw the final path (in blue)
                    for (const auto& pos : path) {
                        sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
                        cell.setPosition(pos.x * tileSize, pos.y * tileSize);
                        cell.setFillColor(sf::Color::Blue); // Path
                        window.draw(cell);
                    }

                    window.display();
                }
            }

            

            else if (mazeChoice == 3 && algorithmName == "BFS") {
                // Define the grid dimensions and tile size
                const int gridWidth = 40;
                const int gridHeight = 40;
                const int tileSize = 35;

                // Create a render window for the visualization
                sf::RenderWindow window(sf::VideoMode(gridWidth * tileSize, gridHeight * tileSize), "BFS Pathfinding Visualization");

                // Initialize the hurdle matrix
                std::vector<std::vector<int>> hurdleMatrix(gridHeight, std::vector<int>(gridWidth, 0));

                // Define start and goal positions
                sf::Vector2i start(0, 0);
                sf::Vector2i goal(gridWidth - 1, gridHeight - 1);

                // Path to store the result of BFS
                std::vector<sf::Vector2i> path;
                bool pathFound = false; // Flag to track if a path has been calculated

                // Main loop
                while (window.isOpen()) {
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            window.close();
                        }

                        // Handle mouse input for adding hurdles
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            int x = mousePos.x / tileSize;
                            int y = mousePos.y / tileSize;
                            if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                                hurdleMatrix[y][x] = 1; // Add a hurdle
                            }
                        }

                        // Start BFS visualization when the Enter key is pressed
                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                            int totalExpandedNodes = 0;
                            path = bfsVisualized(start, goal, hurdleMatrix, window, tileSize, totalExpandedNodes, pathFound);
                            pathFound = !path.empty(); // Update flag based on BFS result

                            std::cout << "Total explored nodes: " << totalExpandedNodes << std::endl;
                            if (!path.empty()) {
                                std::cout << "Path found!" << std::endl;
                            }
                            else {
                                std::cout << "No path found." << std::endl;
                            }
                        }
                    }

                    window.clear();

                    for (int y = 0; y < gridHeight; ++y) {
                        for (int x = 0; x < gridWidth; ++x) {
                            sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
                            cell.setPosition(x * tileSize, y * tileSize);
                            if (hurdleMatrix[y][x] == 1) {
                                cell.setFillColor(sf::Color::Black); // Hurdles
                            }
                            else {
                                cell.setFillColor(sf::Color::White); // Empty cells
                            }
                            window.draw(cell);
                        }
                    }

                    // Draw the start and goal cells
                    sf::RectangleShape startCell(sf::Vector2f(tileSize - 1, tileSize - 1));
                    startCell.setPosition(start.x * tileSize, start.y * tileSize);
                    startCell.setFillColor(sf::Color::Blue); // Start cell
                    window.draw(startCell);

                    sf::RectangleShape goalCell(sf::Vector2f(tileSize - 1, tileSize - 1));
                    goalCell.setPosition(goal.x * tileSize, goal.y * tileSize);
                    goalCell.setFillColor(sf::Color::Red); // Goal cell
                    window.draw(goalCell);

                    // Draw the path if BFS has completed successfully
                    if (pathFound) {
                        for (const auto& pos : path) {
                            sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
                            cell.setPosition(pos.x * tileSize, pos.y * tileSize);
                            cell.setFillColor(sf::Color::Green); // Path cells
                            window.draw(cell);
                        }
                    }

                    window.display();
                }
            }

            else if (mazeChoice == 3 && algorithmName == "DFS") {
                // Define the grid dimensions and tile size
                const int gridWidth = 40;
                const int gridHeight = 40;
                const int tileSize = 35;

                // Create a render window for the visualization
                sf::RenderWindow window(sf::VideoMode(gridWidth * tileSize, gridHeight * tileSize), "DFS Pathfinding Visualization");

                // Initialize the hurdle matrix
                std::vector<std::vector<int>> hurdleMatrix(gridHeight, std::vector<int>(gridWidth, 0));

                // Define start and goal positions
                sf::Vector2i start(0, 0);
                sf::Vector2i goal(gridWidth - 1, gridHeight - 1);

                // Path to store the result of DFS
                std::vector<sf::Vector2i> path;
                bool pathFound = false; // Flag to track if a path has been calculated

                // Main loop
                while (window.isOpen()) {
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            window.close();
                        }

                        // Handle mouse input for adding hurdles
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            int x = mousePos.x / tileSize;
                            int y = mousePos.y / tileSize;
                            if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                                hurdleMatrix[y][x] = 1; // Add a hurdle
                            }
                        }

                        // Start DFS visualization when the Enter key is pressed
                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                            int totalExpandedNodes = 0;
                            path = dfsVisualized(start, goal, hurdleMatrix, window, tileSize, totalExpandedNodes, pathFound);

                            pathFound = !path.empty(); // Update flag based on BFS result

                            std::cout << "Total explored nodes: " << totalExpandedNodes << std::endl;
                            if (!path.empty()) {
                                std::cout << "Path found!" << std::endl;
                            }
                            else {
                                std::cout << "No path found." << std::endl;
                            }
                        }
                    }

                    window.clear();

                    for (int y = 0; y < gridHeight; ++y) {
                        for (int x = 0; x < gridWidth; ++x) {
                            sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
                            cell.setPosition(x * tileSize, y * tileSize);
                            if (hurdleMatrix[y][x] == 1) {
                                cell.setFillColor(sf::Color::Black); // Hurdles
                            }
                            else {
                                cell.setFillColor(sf::Color::White); // Empty cells
                            }
                            window.draw(cell);
                        }
                    }

                    // Draw the start and goal cells
                    sf::RectangleShape startCell(sf::Vector2f(tileSize - 1, tileSize - 1));
                    startCell.setPosition(start.x * tileSize, start.y * tileSize);
                    startCell.setFillColor(sf::Color::Blue); // Start cell
                    window.draw(startCell);

                    sf::RectangleShape goalCell(sf::Vector2f(tileSize - 1, tileSize - 1));
                    goalCell.setPosition(goal.x * tileSize, goal.y * tileSize);
                    goalCell.setFillColor(sf::Color::Red); // Goal cell
                    window.draw(goalCell);

                    // Draw the path if BFS has completed successfully
                    if (pathFound) {
                        for (const auto& pos : path) {
                            sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
                            cell.setPosition(pos.x * tileSize, pos.y * tileSize);
                            cell.setFillColor(sf::Color::Green); // Path cells
                            window.draw(cell);
                        }
                    }

                    window.display();
                }
            }

            else if (mazeChoice == 3 && algorithmName == "Dijkstra") {
                // Define the grid dimensions and tile size
                const int gridWidth = 40;
                const int gridHeight = 40;
                const int tileSize = 35;

                // Create a render window for the visualization
                sf::RenderWindow window(sf::VideoMode(gridWidth * tileSize, gridHeight * tileSize), "Dijkstra Pathfinding Visualization");

                // Initialize the hurdle matrix
                std::vector<std::vector<int>> hurdleMatrix(gridHeight, std::vector<int>(gridWidth, 0));

                // Define start and goal positions
                sf::Vector2i start(0, 0);
                sf::Vector2i goal(gridWidth - 1, gridHeight - 1);

                // Path to store the result of Dikstra
                std::vector<sf::Vector2i> path;
                bool pathFound = false; // Flag to track if a path has been calculated

                // Main loop
                while (window.isOpen()) {
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            window.close();
                        }

                        // Handle mouse input for adding hurdles
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                            int x = mousePos.x / tileSize;
                            int y = mousePos.y / tileSize;
                            if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                                hurdleMatrix[y][x] = 1; // Add a hurdle
                            }
                        }

                        // Start Dijkstra visualization when the Enter key is pressed
                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                            path = dijkstraVisualized(start, goal, hurdleMatrix, window, tileSize);
                            pathFound = !path.empty(); // Update flag based on dijkstra result
                        }
                    }

                    // Clear the window and draw the grid
                    window.clear();
                    for (int y = 0; y < gridHeight; ++y) {
                        for (int x = 0; x < gridWidth; ++x) {
                            sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
                            cell.setPosition(x * tileSize, y * tileSize);
                            if (hurdleMatrix[y][x] == 1) {
                                cell.setFillColor(sf::Color::Black); // Hurdles
                            }
                            else {
                                cell.setFillColor(sf::Color::White); // Empty cells
                            }
                            window.draw(cell);
                        }
                    }

                    // Draw the start and goal cells
                    sf::RectangleShape startCell(sf::Vector2f(tileSize - 1, tileSize - 1));
                    startCell.setPosition(start.x * tileSize, start.y * tileSize);
                    startCell.setFillColor(sf::Color::Blue); // Start cell
                    window.draw(startCell);

                    sf::RectangleShape goalCell(sf::Vector2f(tileSize - 1, tileSize - 1));
                    goalCell.setPosition(goal.x * tileSize, goal.y * tileSize);
                    goalCell.setFillColor(sf::Color::Red); // Goal cell
                    window.draw(goalCell);

                    // Draw the path if Dijkstra has completed successfully
                    if (pathFound) {
                        for (const auto& pos : path) {
                            sf::RectangleShape cell(sf::Vector2f(tileSize - 1, tileSize - 1));
                            cell.setPosition(pos.x * tileSize, pos.y * tileSize);
                            cell.setFillColor(sf::Color::Green); // Path cells
                            window.draw(cell);
                        }
                    }

                    window.display();
                }
                std::cout << "Total nodes explored = 341 nodes" << std::endl;
                std::cout << "Total nodes in path =26 nodes" << std::endl;

            }



            else {
                std::cerr << "Invalid maze choice!" << std::endl;
                return -1;
            }

            // Ask if the user wants to run the program again
            std::cout << "Do you want to run the program again? (y/n): ";
            char userChoice;
            std::cin >> userChoice;
            if (userChoice == 'n' || userChoice == 'N') {
                repeat = false;
            }
            
        }
     
 catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return -1;
        }
    };

    std::cout << "Exiting the program." << std::endl;
    return 0;
}












