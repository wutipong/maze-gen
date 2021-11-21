#include "maze.hpp"
#include "maze_context.hpp"

#include <random>

using namespace MazeGen;

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

    from.pConnectedCells[static_cast<size_t>(direction)] = &to;
}

Maze MazeGen::Generate(size_t column, size_t row, OnProgress onProgressCallback, LogFunc log, RandomCellFunc randomCell,
                       RandomDirectionFunc randomDirection)
{
    Maze maze{column, row};
    MazeContext ctx = MazeContext{column, row};
    int progress = 0;
    const int total = ctx.cellCount;

    for (progress = 0; ctx.SetCount() != 1; progress++)
    {
        onProgressCallback(progress, total);

        auto [from, to, direction, opposite] = ctx.RandomJoin(randomCell, randomDirection);

        log(from, to);

        auto &fromCell = maze.cells[from];
        auto &toCell = maze.cells[to];

        Connect(fromCell, toCell, direction);
        Connect(toCell, fromCell, opposite);
    }

    onProgressCallback(total, total);

    return maze;
}

Cell *MazeGen::Cell::ConnectedCell(Direction direction)
{
    return pConnectedCells[static_cast<int>(direction)];
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
