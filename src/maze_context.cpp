#include "maze.hpp"
#include <set>

using namespace MazeGen;

MazeContext::MazeContext(size_t row, size_t column) : row(row), column(column), cellCount(row * column)
{
    disjointSets.reserve(cellCount);
    for (size_t i = 0; i < cellCount; i++)
    {
        std::shared_ptr<std::set<size_t>> ptr{new std::set<size_t>()};
        ptr->emplace(i);

        disjointSets.emplace_back(ptr);
    }
}

bool MazeContext::JoinSet(size_t to, size_t from)
{
    auto &toSet = disjointSets[to];
    auto &fromSet = disjointSets[from];

    for (auto &c : *fromSet)
    {
        if (toSet->find(c) != toSet->end())
        {
            return false;
        }
    }

    toSet->emplace(fromSet->begin(), fromSet->end());

    fromSet = toSet;

    return true;
}

size_t MazeContext::GetAdjacentCell(size_t cell, Direction direction)
{
    if (cell < 0 || cell >= cellCount)
        return InvalidCell;

    size_t x = cell % row;
    size_t y = cell / row;

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