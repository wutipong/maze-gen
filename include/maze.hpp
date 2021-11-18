#pragma once
#include <memory>
#include <set>
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

struct MazeContext
{
    const size_t row;
    const size_t column;
    const size_t cellCount;

    static constexpr size_t InvalidCell = -1; 
    
    enum class Direction
    {
        North,
        South,
        East,
        West,
    };

    std::vector<std::shared_ptr<std::set<size_t>>> disjointSets;

    MazeContext(size_t row, size_t column);

    bool JoinSet(size_t to, size_t from);

    size_t GetAdjacentCell(size_t cell, Direction direction);
};
} // namespace MazeGen