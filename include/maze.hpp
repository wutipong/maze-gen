#pragma once
#include <memory>
#include <set>
#include <utility>
#include <vector>

namespace MazeGen
{
typedef size_t Connection;

constexpr Connection ToNorth = 1;
constexpr Connection ToSouth = 2;
constexpr Connection ToEast = 4;
constexpr Connection ToWest = 8;

struct Cell
{
    Cell *pNorth{nullptr};
    Cell *pSouth{nullptr};
    Cell *pEast{nullptr};
    Cell *pWest{nullptr};

    Connection connections = 0;
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