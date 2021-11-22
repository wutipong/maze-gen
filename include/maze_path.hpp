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

Path FindPath(Maze &m, int from, int to);
}