#pragma once
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <functional>

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

typedef std::function<int(int maxCell)> RandomCellFunc;
typedef std::function<Direction()> RandomDirectionFunc;
typedef std::function<void(int current, int total)> OnProgress;
typedef std::function<void (int from, int to)> LogFunc;

Direction Opposite(Direction direction);

class Cell
{
  public:
    Cell(int id) : id(id){};
    int ConnectedCell(Direction direction);

    const int Id() const
    {
        return id;
    }

    friend void Connect(Cell &from, Cell &to, Direction direction);

  private:
    const int id;
    int connectedCells[static_cast<int>(Direction::Count)] = {InvalidCell, InvalidCell, InvalidCell, InvalidCell};
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

    Cell &At(int id)
    {
        return cells[id];
    }

    Cell At(int id) const
    {
        return cells[id];
    }

    Cell &operator[](int index)
    {
        return At(index);
    }

    Cell operator[](int index) const
    {
        return At(index);
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
