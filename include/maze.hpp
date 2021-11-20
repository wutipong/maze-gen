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

class MazeContext
{
  public:
    typedef std::set<size_t> Set;
    typedef std::shared_ptr<Set> SetPtr;

    enum class Direction
    {
        North,
        South,
        East,
        West,
    };
    static constexpr size_t InvalidCell = -1;

    const size_t row;
    const size_t column;
    const size_t cellCount;

  private:
    std::vector<SetPtr> disjointSets;
    int setCount;

  public:
    MazeContext(size_t column, size_t row);

    bool JoinSet(size_t to, size_t from);
    size_t GetAdjacentCell(size_t cell, Direction direction);
};
} // namespace MazeGen