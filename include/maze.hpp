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

constexpr int InvalidCell = -1;

typedef int CellFlags;

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

typedef int (*RandomCellFunc)(int maxCell);
typedef Direction (*RandomDirectionFunc)();
typedef void (*OnProgress)(int current, int total);
typedef void (*LogFunc)(int from, int to);

Direction Opposite(Direction direction);

class Cell
{
  public:
    Cell(int id) : id(id){};
    int ConnectedCell(Direction direction);
    CellFlags Flags() const
    {
        return flags;
    }

    const int Id() const
    {
        return id;
    }

    friend void Connect(Cell &from, Cell &to, Direction direction);

  private:
    const int id;
    int connectedCells[static_cast<int>(Direction::Count)] = {InvalidCell, InvalidCell, InvalidCell, InvalidCell};
    CellFlags flags = 0;
};

class Maze
{
  public:
    const int row;
    const int column;
    const int cellCount;

    Maze(int column, int row) : row(row), column(column), cellCount(row * column)
    {
        for (int i = 0; i < cellCount; i++)
        {
            cells.emplace_back(i);
        }
    };

    Cell& At(int id) 
    {
        return cells[id];
    }

    Cell At(int id) const
    {
        return cells[id];
    }

    int AdjacentCellID(int id, Direction direction) const;

  private:
    std::vector<Cell> cells;
};

int RandomCellFuncImpl(int maxCell);
Direction RandomDirectionFuncImpl();

struct GenerateOptions
{
    OnProgress onProgressCallback = [](int current, int total) {};
    LogFunc logFunc = [](int from, int to) {};
    RandomCellFunc randomCellFunc = RandomCellFuncImpl;
    RandomDirectionFunc randomDirectionFunc = RandomDirectionFuncImpl;
};

Maze Generate(int column, int row, GenerateOptions options = {});

} // namespace MazeGen
