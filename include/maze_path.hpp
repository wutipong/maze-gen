#include "maze.hpp"

#include <deque>
namespace MazeGen
{
struct PathNode
{
    size_t cell;
    Direction direction;
};

typedef std::deque<PathNode> Path;

Path FindPath(Maze &m, size_t from, size_t to);
}