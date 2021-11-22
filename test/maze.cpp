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
            REQUIRE((m.cells[i].Flags() & MazeGen::ConnectedToWest) == 0);
            REQUIRE(m.cells[i].ConnectedCell(Direction::West) == nullptr);
        }

        if (x == column - 1)
        {
            REQUIRE((m.cells[i].Flags() & MazeGen::ConnectedToEast) == 0);
            REQUIRE(m.cells[i].ConnectedCell(Direction::East) == nullptr);
        }

        if (y == 0)
        {
            REQUIRE((m.cells[i].Flags() & MazeGen::ConnectedToNorth) == 0);
            REQUIRE(m.cells[i].ConnectedCell(Direction::North) == nullptr);
        }

        if (y == row - 1)
        {
            REQUIRE((m.cells[i].Flags() & MazeGen::ConnectedToSouth) == 0);
            REQUIRE(m.cells[i].ConnectedCell(Direction::South) == nullptr);
        }

        INFO("cell index " << i);
        REQUIRE(m.cells[i].Flags() != 0);
    }
}
