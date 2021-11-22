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
    Count,
    Invalid = -1
};

static constexpr size_t InvalidCell = -1;

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

Direction Opposite(Direction direction);

class Cell
{
  public:
    Cell(size_t id) : id(id){};
    size_t ConnectedCell(Direction direction);
    CellFlags Flags() const
    {
        return flags;
    }

    const size_t Id() const
    {
        return id;
    }

    friend void Connect(Cell &from, Cell &to, Direction direction);

  private:
    const size_t id;
    size_t connectedCells[static_cast<size_t>(Direction::Count)] = {InvalidCell, InvalidCell, InvalidCell, InvalidCell};
    CellFlags flags = 0;
};

class Maze
{
  public:
    const size_t row;
    const size_t column;
    const size_t cellCount;

    Maze(size_t column, size_t row) : row(row), column(column), cellCount(row * column)
    {
        for (size_t i = 0; i < cellCount; i++)
        {
            cells.emplace_back(i);
        }
    };

    Cell At(size_t id) const
    {
        return cells[id];
    }

    size_t AdjacentCellID(size_t id, Direction direction) const;

  private:
    std::vector<Cell> cells;
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
