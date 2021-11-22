#include "maze.hpp"
#include "maze_context.hpp"

#include <random>

using namespace MazeGen;

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

    return Direction::Invalid;
}

void MazeGen::Connect(Cell &from, Cell &to, Direction direction)
{
    switch (direction)
    {
    case Direction::North:
        from.flags |= MazeGen::ConnectedToNorth;
        break;

    case Direction::South:
        from.flags |= MazeGen::ConnectedToSouth;
        break;

    case Direction::East:
        from.flags |= MazeGen::ConnectedToEast;
        break;

    case Direction::West:
        from.flags |= MazeGen::ConnectedToWest;
        break;
    }

    from.connectedCells[static_cast<size_t>(direction)] = to.Id();
}

Maze MazeGen::Generate(size_t column, size_t row, GenerateOptions options)
{
    auto &[onProgressCallback, log, randomCell, randomDirection] = options;

    Maze maze{column, row};
    MazeContext ctx = MazeContext{column, row};
    int progress = 0;
    const int total = ctx.cellCount;

    for (progress = 0; ctx.SetCount() != 1; progress++)
    {
        onProgressCallback(progress, total);

        auto [from, to, direction, opposite] = ctx.RandomJoin(randomCell, randomDirection);

        log(from, to);

        auto fromCell = maze.At(from);
        auto toCell = maze.At(to);

        Connect(fromCell, toCell, direction);
        Connect(toCell, fromCell, opposite);
    }

    onProgressCallback(total, total);

    return maze;
}

size_t MazeGen::Cell::ConnectedCell(Direction direction)
{
    return connectedCells[static_cast<int>(direction)];
}

size_t MazeGen::RandomCellFuncImpl(size_t maxCell)
{
    static std::random_device r;

    std::default_random_engine e(r());

    // maximum value is exclusive.
    std::uniform_int_distribution<size_t> uniform_dist(0, maxCell - 1);

    return uniform_dist(e);
}

Direction MazeGen::RandomDirectionFuncImpl()
{
    static std::random_device r;

    std::default_random_engine e(r());

    // maximum value is exclusive.
    std::uniform_int_distribution<int> uniform_dist(0, static_cast<size_t>(Direction::Count) - 1);

    return static_cast<Direction>(uniform_dist(e));
}

size_t MazeGen::Maze::AdjacentCellID(size_t id, Direction direction) const
{
    if (id < 0 || id >= cellCount)
        return InvalidCell;

    size_t x = id % column;
    size_t y = id / column;

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
