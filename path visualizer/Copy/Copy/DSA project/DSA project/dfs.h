#pragma once
#pragma once
#include <vector>
#include <functional>
#include "Node.h"

bool dfs(std::vector<std::vector<Node>>& grid, Node& start, Node& end,
    std::function<void(const std::vector<std::vector<Node>>&)> visualizeCallback = nullptr);
