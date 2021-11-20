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
    const size_t row;
    const size_t column;

    std::vector<Cell> cells;
    Maze(size_t column, size_t row) : row(row), column(column)
    {
        cells.resize(column * row);
    };
};

typedef void (*OnProgress)(int current, int total);

Maze Generate(size_t column, size_t row, OnProgress onProgressCallback = nullptr);
} // namespace MazeGen