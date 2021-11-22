#include "maze.hpp"
#include <catch2/catch.hpp>

using namespace MazeGen;
TEST_CASE("Generate", "[Maze]")
{
    constexpr size_t column = 50, row = 50;

    auto m = MazeGen::Generate(column, row);

    for (int i = 0; i < row * column; i++)
    {
        int x = i % column;
        int y = i / column;

        if (x == 0)
        {
            INFO("Cell [" << x << "," << y << "]");
            REQUIRE((m.At(i).Flags() & MazeGen::ConnectedToWest) == 0);
            REQUIRE(m.At(i).ConnectedCell(Direction::West) == InvalidCell);
        }

        if (x == column - 1)
        {
            INFO("Cell [" << x << "," << y << "]");
            REQUIRE((m.At(i).Flags() & MazeGen::ConnectedToEast) == 0);
            REQUIRE(m.At(i).ConnectedCell(Direction::East) == InvalidCell);
        }

        if (y == 0)
        {
            INFO("Cell [" << x << "," << y << "]");
            REQUIRE((m.At(i).Flags() & MazeGen::ConnectedToNorth) == 0);
            REQUIRE(m.At(i).ConnectedCell(Direction::North) == InvalidCell);
        }

        if (y == row - 1)
        {
            INFO("Cell [" << x << "," << y << "]");
            REQUIRE((m.At(i).Flags() & MazeGen::ConnectedToSouth) == 0);
            REQUIRE(m.At(i).ConnectedCell(Direction::South) == InvalidCell);
        }

        INFO("cell index " << i);
        REQUIRE(m.At(i).Flags() != 0);
    }
}
