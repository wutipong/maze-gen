#pragma once
#include <memory>
#include <set>
#include <utility>
#include <vector>

namespace MazeGen
{
struct Cell
{
    Cell *pNorth{nullptr};
    Cell *pSouth{nullptr};
    Cell *pEast{nullptr};
    Cell *pWest{nullptr};
};

struct Maze
{
    const int row;
    const int column;

    std::vector<Cell> cells;
    Maze(int row, int column) : row(row), column(column){};
};
} // namespace MazeGen