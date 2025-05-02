# Path Visualizer

A C++ implementation of various pathfinding algorithms with visualization capabilities.

## Overview

This project provides implementations of several popular pathfinding algorithms used in computer science and artificial intelligence. The visualizer allows users to see how different algorithms traverse a graph or maze to find the optimal path between two points.

## Algorithms Implemented

- **A*** (A-star): Uses heuristics to efficiently find the shortest path
- **BFS** (Breadth-First Search): Explores all neighbor nodes at the present depth before moving to nodes at the next depth
- **DFS** (Depth-First Search): Explores as far as possible along each branch before backtracking
- **Dijkstra's Algorithm**: Finds the shortest path between nodes in a graph
- **Dynamic Versions**: Implementations that can handle changes in the graph/maze during execution

## Features

- Interactive maze construction
- Visualization of algorithm execution steps
- Comparison of algorithm performance
- Support for weighted and unweighted graphs
- Hurdle maze capabilities for testing algorithm performance in complex environments
- Numeric weighted maze support for more realistic pathfinding scenarios

## Requirements

- C++ compiler with C++11 support or later
- Visual Studio (solution file included)

## Usage

1. Clone the repository
2. Open the solution file in Visual Studio
3. Build and run the project
4. Use the interface to:
   - Select an algorithm
   - Create or load a maze
   - Set start and end points
   - Run the visualization

## Project Structure

- `astar.cpp/h`: A* algorithm implementation
- `bfs.cpp/h`: Breadth-First Search implementation
- `dfs.cpp/h`: Depth-First Search implementation
- `dijkstra.cpp/h`: Dijkstra's algorithm implementation
- `*dynamic.cpp/h`: Dynamic versions of the algorithms
- `hurdleMaze.cpp/h`: Implementation for creating and managing maze with obstacles
- `NumericWeightedMaze.cpp/h`: Implementation for mazes with numeric weights
- `Node.h`: Node structure used by the algorithms
- `main.cpp`: Entry point for the application

## Future Enhancements

- Additional algorithms (Bidirectional Search, Jump Point Search, etc.)
- Performance metrics and algorithm comparisons
- More maze generation algorithms
- Export/import maze configurations

