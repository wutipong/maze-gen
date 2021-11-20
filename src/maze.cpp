#include <maze.hpp>
#include <maze_context.hpp>

using namespace MazeGen;

namespace
{
Cell *&Adjacent(Cell &cell, Direction direction)
{
    switch (direction)
    {
    case Direction::North:
        return cell.pNorth;

    case Direction::South:
        return cell.pSouth;

    case Direction::East:
        return cell.pEast;

    case Direction::West:
        return cell.pWest;
    }

    throw 0;
}

void AddConnection(Cell &from, Cell &to, Direction direction)
{
    switch (direction)
    {
    case Direction::North:
        from.connections |= MazeGen::ToNorth;
        break;

    case Direction::South:
        from.connections |= MazeGen::ToSouth;
        break;

    case Direction::East:
        from.connections |= MazeGen::ToEast;
        break;

    case Direction::West:
        from.connections |= MazeGen::ToWest;
        break;
    }

    Adjacent(from, direction) = &to;
}
} // namespace

Maze MazeGen::Generate(size_t column, size_t row, OnProgress onProgressCallback)
{
    Maze maze{column, row};
    MazeContext ctx = MazeContext{column, row};
    int progress = 0;
    const int total = ctx.cellCount;

    for (progress = 0; ctx.SetCount() != 1; progress++)
    {
        if (onProgressCallback != nullptr)
            onProgressCallback(progress, total);

        auto [from, to, direction, opposite] = ctx.RandomJoin();

        auto &fromCell = maze.cells[from];
        auto &toCell = maze.cells[to];

        AddConnection(fromCell, toCell, direction);
        AddConnection(toCell, fromCell, opposite);
    }

    if (onProgressCallback != nullptr)
        onProgressCallback(total, total);

    return maze;
}