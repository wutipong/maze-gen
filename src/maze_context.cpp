#include "maze_context.hpp"
#include <random>
#include <set>

using namespace MazeGen;

MazeContext::MazeContext(size_t column, size_t row)
    : row(row), column(column), cellCount(row * column), setCount(cellCount)
{
    disjointSets.reserve(cellCount);
    for (size_t i = 0; i < cellCount; i++)
    {
        auto ptr = std::make_shared<Set>();
        ptr->emplace(i);

        disjointSets.emplace_back(ptr);
    }
}

bool MazeContext::TryJoinSet(size_t to, size_t from)
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

    toSet->insert(fromSet->begin(), fromSet->end());

    fromSet = toSet;
    setCount = setCount - 1;

    return true;
}

size_t MazeContext::GetAdjacentCell(size_t cell, Direction direction)
{
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

size_t MazeContext::RandomCellFuncImpl(size_t maxCell)
{
    static std::random_device r;

    std::default_random_engine e(r());
    std::uniform_int_distribution<size_t> uniform_dist(0, maxCell);

    return uniform_dist(e);
}

Direction MazeContext::RandomDirectionFuncImpl()
{
    static std::random_device r;

    std::default_random_engine e(r());
    std::uniform_int_distribution<int> uniform_dist(0, static_cast<size_t>(Direction::Count));

    return static_cast<Direction>(uniform_dist(e));
}

MazeContext::JoinResult MazeContext::RandomJoin(RandomCellFunc randomCell, RandomDirectionFunc randomDirection)
{
    while (true)
    {
        auto fromCell = randomCell(cellCount);
        auto direction = randomDirection();
        auto toCell = GetAdjacentCell(fromCell, direction);
        if (TryJoinSet(toCell, fromCell))
        {
            return {fromCell, toCell, direction, Opposite(direction)};
        }
    }
}

Direction MazeGen::Opposite(Direction direction)
{
    switch (direction)
    {
    case Direction::North:
        return Direction::South;
    case Direction::South:
        return Direction::North;
    case Direction::East:
        return Direction::West;
    case Direction::West:
        return Direction::East;
    }

    return Direction::Count;
}