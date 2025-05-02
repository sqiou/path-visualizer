#include "dfs.h"
#include <stack>
#include <functional>

bool dfs(std::vector<std::vector<Node>>& grid, Node& start, Node& end,
    std::function<void(const std::vector<std::vector<Node>>&)> visualizeCallback) {
    if (grid.empty() || grid[0].empty()) {
        return false;
    }

    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    // Reset all nodes
    for (auto& row : grid) {
        for (auto& node : row) {
            node.isVisited = false;
            node.parent = nullptr;
        }
    }

    std::stack<Node*> stack;
    stack.push(&start);
    start.isVisited = true;

    while (!stack.empty()) {
        Node* current = stack.top();
        stack.pop();

        if (current == &end) {
            return true;
        }

        const int dx[] = { 0, 1, 0, -1 };
        const int dy[] = { -1, 0, 1, 0 };

        for (int i = 0; i < 4; ++i) {
            int newX = current->position.first + dx[i];
            int newY = current->position.second + dy[i];

            if (newX >= 0 && newX < cols && newY >= 0 && newY < rows) {
                Node& neighbor = grid[newY][newX];

                if (!neighbor.isHurdle && !neighbor.isVisited) {
                    neighbor.isVisited = true;
                    neighbor.parent = current;
                    stack.push(&neighbor);
                }
            }
        }
        if (visualizeCallback) {
            visualizeCallback(grid);
        }
    }

    return false;
}
