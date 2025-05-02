#pragma once
#include <vector>
#include <functional>
#include "Node.h"

void astar(std::vector<std::vector<Node>>& grid, Node& start, Node& goal,
    std::function<void(const std::vector<std::vector<Node>>&)> visualizeCallback);
