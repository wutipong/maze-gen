#include "maze_path.hpp"

#include <stack>

using namespace MazeGen;

typedef std::stack<PathNode, Path> PathNodeStack;


Path MazeGen::FindPath(Maze &m, size_t from, size_t to)
{
    size_t current = from;
    Path p;
    PathNodeStack stack(p);

    while (current != to)
    {
        Direction fromDirection = Direction::Invalid;
        if (stack.size() > 0)
        {
            fromDirection = Opposite(stack.top().direction);
        }
        
    }

    return p;
}