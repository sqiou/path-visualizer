#include "astar.h"
#include "Node.h"
#include <queue>
#include <cmath>
#include <functional>
#include <iostream>
#include <unordered_set>

struct CompareNode {
    bool operator()(const Node* a, const Node* b) const {
        return a->fCost() > b->fCost(); // Min-heap based on fCost
    }
};

float calculateHeuristic(const Node& a, const Node& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y); // Manhattan Distance
}

void astar(std::vector<std::vector<Node>>& grid, Node& start, Node& goal,
    std::function<void(const std::vector<std::vector<Node>>&)> visualizeCallback) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;
    std::unordered_set<Node*> closedList;

    // Initialize all nodes in the grid
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[0].size(); ++x) {
            grid[y][x].gCost = std::numeric_limits<float>::infinity();
            grid[y][x].hCost = std::numeric_limits<float>::infinity();
            grid[y][x].isVisited = false;
            grid[y][x].parent = nullptr;

            // Ensure start and goal nodes are not hurdles
            if ((y == start.y && x == start.x) || (y == goal.y && x == goal.x)) {
                grid[y][x].isHurdle = false;
            }
        }
    }

    // Initialize start node
    start.gCost = 0;
    start.hCost = calculateHeuristic(start, goal);
    openList.push(&start);

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        // Mark current node as visited
        closedList.insert(current);
        current->isVisited = true;

        // Check if the goal is reached
        if (current == &goal) {
            std::cout << "Goal reached at (" << goal.x << ", " << goal.y << ")\n";
            return; // Path found
        }

        // Neighbor exploration (4 directions)
        const int dx[] = { 0, 1, 0, -1 };
        const int dy[] = { -1, 0, 1, 0 };

        for (int i = 0; i < 4; i++) {
            int newX = current->x + dx[i];
            int newY = current->y + dy[i];

            // Ensure neighbors are within bounds
            if (newX >= 0 && newX < grid[0].size() && newY >= 0 && newY < grid.size()) {
                Node& neighbor = grid[newY][newX];

                // Skip if it's a hurdle, already visited, or in the closed list
                if (neighbor.isHurdle) {
                    std::cout << "Skipping hurdle at (" << newX << ", " << newY << ")\n";
                    continue;
                }
                if (closedList.count(&neighbor)) {
                    continue;
                }

                // Calculate tentative gCost
                float tentativeGCost = current->gCost + (neighbor.hasWeight ? neighbor.weight : 1);

                // Check if the path to the neighbor is better or unvisited
                if (tentativeGCost < neighbor.gCost) {
                    neighbor.gCost = tentativeGCost;
                    neighbor.hCost = calculateHeuristic(neighbor, goal);
                    neighbor.parent = current;

                    // Add to open list if not visited
                    if (!neighbor.isVisited) {
                        openList.push(&neighbor);
                        neighbor.isVisited = true;
                    }
                }
            }
        }

        // Visualize the step
        if (visualizeCallback) {
            visualizeCallback(grid);
        }
    }

    std::cerr << "No path found!\n";
}
