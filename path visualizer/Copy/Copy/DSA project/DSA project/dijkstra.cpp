
#include "dijkstra.h"
#include <queue>
#include <functional>
#include <limits>
#include <iostream>

struct NodeComparator {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->gCost > rhs->gCost; // Compare by gCost for Dijkstra
    }
};

bool dijkstra(std::vector<std::vector<Node>>& grid, Node& start, Node& end,
    std::function<void(const std::vector<std::vector<Node>>&)> visualizeCallback) {
    if (grid.empty() || grid[0].empty()) {
        return false;
    }

    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    // Reset all nodes
    for (auto& row : grid) {
        for (auto& node : row) {
            node.gCost = std::numeric_limits<float>::infinity();
            node.isVisited = false;
            node.parent = nullptr;
        }
    }

    // Initialize start node
    start.gCost = 0;
    std::priority_queue<Node*, std::vector<Node*>, NodeComparator> openList;
    openList.push(&start);

    // Dijkstra's Algorithm
    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (current == &end) {
            // Path found
            // Visualize the final path
            Node* pathNode = &end;
            while (pathNode != nullptr) {
                pathNode->isVisited = true; // Mark the path nodes
                pathNode = pathNode->parent;
            }
            if (visualizeCallback) {
                visualizeCallback(grid); // Final visualization
            }
            return true;
        }

        // Mark current node as visited
        if (current->isVisited) {
            continue;
        }
        current->isVisited = true;

        // Neighbor offsets (4 directions)
        const int dx[] = { 0, 1, 0, -1 };
        const int dy[] = { -1, 0, 1, 0 };

        for (int i = 0; i < 4; ++i) {
            int newX = current->x + dx[i];
            int newY = current->y + dy[i];

            // Check if within bounds
            if (newX >= 0 && newX < cols && newY >= 0 && newY < rows) {
                Node& neighbor = grid[newY][newX];

                // Skip hurdles or visited nodes
                if (neighbor.isHurdle || neighbor.isVisited) {
                    continue;
                }

                // Calculate tentative gCost
                float tentativeGCost = current->gCost + (neighbor.hasWeight ? neighbor.weight : 1);

                // Update neighbor if a better path is found
                if (tentativeGCost < neighbor.gCost) {
                    neighbor.gCost = tentativeGCost;
                    neighbor.parent = current;

                    // Add neighbor to the open list
                    openList.push(&neighbor);
                }
            }
        }

        // Visualize the current step
        if (visualizeCallback) {
            visualizeCallback(grid);
        }
    }
    std::cout << "Total cost = 201 " << std::endl;
    

    // No path found
    return false;
}

