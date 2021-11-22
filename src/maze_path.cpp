#include "maze_path.hpp"

#include <iostream>
#include <stack>

using namespace MazeGen;

namespace
{
Direction Next(Direction direction)
{
    switch (direction)
    {
    case Direction::Invalid:
        return Direction::North;
    case Direction::North:
        return Direction::East;
    case Direction::East:
        return Direction::South;
    case Direction::South:
        return Direction::West;
    case Direction::West:
        return Direction::Invalid;
    }

    return Direction::Invalid;
}
} // namespace

Path MazeGen::FindPath(Maze &m, int from, int to)
{
    Path p;

    p.push_back(PathNode{.cell = from, .fromDirection = Direction::Invalid, .toDirection = Direction::Invalid});

    if (from == to)
    {
        return p;
    }

    while (true)
    {
        auto &currentNode = p.back();
        if (currentNode.cell == to)
            break;

        auto &cell = m.At(currentNode.cell);

        currentNode.toDirection = Next(currentNode.toDirection);
        if (currentNode.toDirection == Direction::Invalid)
        {
            p.pop_back();
            continue;
        }

        if (currentNode.toDirection == currentNode.fromDirection)
        {
            continue;
        }

        auto nextCell = cell.ConnectedCell(currentNode.toDirection);
        if (nextCell == InvalidCell)
        {
            continue;
        }

        PathNode next{.cell = m.AdjacentCellID(currentNode.cell, currentNode.toDirection),
                      .fromDirection = Opposite(currentNode.toDirection),
                      .toDirection = Direction::Invalid};

        p.push_back(next);
    }

    return p;
}