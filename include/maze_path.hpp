#include "maze.hpp"

#include <vector>
namespace MazeGen
{
struct PathNode
{
    size_t cell;
    Direction fromDirection;
    Direction toDirection;
};

typedef std::vector<PathNode> Path;

Path FindPath(Maze &m, size_t from, size_t to);
}