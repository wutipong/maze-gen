#pragma once

#include "maze.hpp"

#include <vector>
namespace MazeGen
{
struct PathNode
{
    int cell;
    Direction fromDirection;
    Direction toDirection;
};

typedef std::vector<PathNode> Path;

// Depth-first search
Path FindPathDFS(Maze &m, int from, int to);

// Breadth-first search
Path FindPathBFS(Maze &m, int from, int to);
}