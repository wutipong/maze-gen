#include "maze_path.hpp"

#include <stack>
#include <iostream>

using namespace MazeGen;

typedef std::stack<PathNode, Path> PathNodeStack;

namespace
{
constexpr size_t InvalidCell = -1;
Direction Next(Direction direction)
{
    switch (direction)
    {
    case Direction::Invalid:
        return Direction::North;
    case Direction::North:
        return Direction::South;
    case Direction::South:
        return Direction::East;
    case Direction::East:
        return Direction::West;
    case Direction::West:
        return Direction::Invalid;
    }

    return Direction::Invalid;
}

size_t GetAdjacentCell(size_t cell, size_t row, size_t column, Direction direction)
{
    auto cellCount = row * column;

    if (cell < 0 || cell >= cellCount)
        return InvalidCell;

    size_t x = cell % column;
    size_t y = cell / column;

    switch (direction)
    {
    case Direction::North:
        y = y - 1;
        break;

    case Direction::South:
        y = y + 1;
        break;

    case Direction::West:
        x = x - 1;
        break;
    case Direction::East:
        x = x + 1;
        break;
    }

    if (x < 0 || x >= column)
        return InvalidCell;

    if (y < 0 || y >= row)
        return InvalidCell;

    return (y * column) + x;
}
} // namespace

Path MazeGen::FindPath(Maze &m, size_t from, size_t to)
{
    size_t current = from;
    Path p;
    PathNodeStack stack(p);

    stack.push(PathNode{.cell = from, .fromDirection = Direction::Invalid, .toDirection = Direction::Invalid});

    if (from == to)
    {
        return p;
    }

    while (current != to)
    {
        auto &current = stack.top();
        auto &cell = m.cells[current.cell];

        current.toDirection = Next(current.toDirection);
        if (current.toDirection == Direction::Invalid)
        {
            stack.pop();
            continue;
        }

        if (current.toDirection == current.fromDirection)
        {
            continue;
        }

        auto nextCell = cell.ConnectedCell(current.toDirection);
        if (nextCell == nullptr)
        {
            continue;
        }

        PathNode next{.cell = GetAdjacentCell(current.cell, m.row, m.column, current.toDirection),
                      .fromDirection = Opposite(current.toDirection),
                      .toDirection = Direction::Invalid};

        std::cout << "going to " << next.cell << std::endl;

        stack.push(next);
    }

    return p;
}