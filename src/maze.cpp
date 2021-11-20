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
} // namespace

Maze Generate(size_t column, size_t row, OnProgress onProgressCallback)
{
    Maze maze{column, row};
    MazeContext ctx = MazeContext{column, row};
    int progress = 0;
    const int total = ctx.cellCount;

    for (progress = 0; ctx.SetCount() != 1; progress++)
    {
        if (onProgressCallback != nullptr)
            onProgressCallback(progress, total);

        auto result = ctx.RandomJoin();

        auto &fromCell = maze.cells[result.from];
        auto &toCell = maze.cells[result.to];

        Adjacent(fromCell, result.direction) = &toCell;
        Adjacent(toCell, result.opposite) = &fromCell;
    }

    return maze;
}