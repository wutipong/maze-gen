#pragma once
#include <memory>
#include <set>
#include <utility>
#include <vector>

namespace MazeGen
{

enum class Direction
{
    North,
    South,
    East,
    West,
    Count
};

typedef size_t CellFlags;

constexpr CellFlags ConnectedToNorth = 1;
constexpr CellFlags ConnectedToSouth = 2;
constexpr CellFlags ConnectedToEast = 4;
constexpr CellFlags ConnectedToWest = 8;
constexpr CellFlags ConnectedToNorthAndSouth = ConnectedToNorth | ConnectedToSouth;
constexpr CellFlags ConnectedToNorthAndEast = ConnectedToNorth | ConnectedToEast;
constexpr CellFlags ConnectedToNorthAndWest = ConnectedToNorth | ConnectedToWest;
constexpr CellFlags ConnectedToSouthAndEast = ConnectedToSouth | ConnectedToEast;
constexpr CellFlags ConnectedToSouthAndWest = ConnectedToSouth | ConnectedToWest;
constexpr CellFlags ConnectedToEastAndWest = ConnectedToEast | ConnectedToWest;
constexpr CellFlags ConnectedToNorthSouthAndEast = ConnectedToNorth | ConnectedToSouth | ConnectedToEast;
constexpr CellFlags ConnectedToNorthSouthAndWest = ConnectedToNorth | ConnectedToSouth | ConnectedToWest;
constexpr CellFlags ConnectedToNorthEastAndWest = ConnectedToNorth | ConnectedToEast | ConnectedToWest;
constexpr CellFlags ConnectedToSouthEastAndWest = ConnectedToSouth | ConnectedToEast | ConnectedToWest;
constexpr CellFlags ConnectedToAll = ConnectedToNorth | ConnectedToSouth | ConnectedToEast | ConnectedToWest;

typedef size_t (*RandomCellFunc)(size_t maxCell);
typedef Direction (*RandomDirectionFunc)();
typedef void (*OnProgress)(int current, int total);
typedef void (*LogFunc)(size_t from, size_t to);

class Cell
{
  public:
    Cell *ConnectedCell(Direction direction);
    CellFlags Flags() const
    {
        return flags;
    }

    friend void Connect(Cell &from, Cell &to, Direction direction);

  private:
    Cell *pConnectedCells[static_cast<size_t>(Direction::Count)] = {nullptr};
    CellFlags flags = 0;
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

size_t RandomCellFuncImpl(size_t maxCell);
Direction RandomDirectionFuncImpl();

struct GenerateOptions
{
    OnProgress onProgressCallback = [](int current, int total) {};
    LogFunc logFunc = [](size_t from, size_t to) {};
    RandomCellFunc randomCellFunc = RandomCellFuncImpl;
    RandomDirectionFunc randomDirectionFunc = RandomDirectionFuncImpl;
};

Maze Generate(size_t column, size_t row, GenerateOptions options = {});

} // namespace MazeGen
