#include "maze.hpp"
#include <catch2/catch.hpp>

using namespace MazeGen;
TEST_CASE("Generate", "[Maze]")
{
    constexpr int column = 50, row = 50;

    auto m = MazeGen::Generate(column, row);

    for (int i = 0; i < row * column; i++)
    {
        auto [x, y] = m.CellPosition(i);

        INFO("Cell #" << i << " [" << x << ", " << y << "]");
        if (x == 0)
        {
            REQUIRE(m.At(i).ConnectedCell(Direction::West) == InvalidCell);
        }

        if (x == column - 1)
        {
            REQUIRE(m.At(i).ConnectedCell(Direction::East) == InvalidCell);
        }

        if (y == 0)
        {
            REQUIRE(m.At(i).ConnectedCell(Direction::North) == InvalidCell);
        }

        if (y == row - 1)
        {
            REQUIRE(m.At(i).ConnectedCell(Direction::South) == InvalidCell);
        }
    }
}
