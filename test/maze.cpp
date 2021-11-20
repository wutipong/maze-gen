#include <catch2/catch.hpp>

#include "maze.hpp"

TEST_CASE("Generate", "[Maze]")
{
    constexpr size_t column = 500, row = 200;
 
    auto m = MazeGen::Generate(column, row);

    for (int i = 0; i < row * column; i++)
    {
        int x = i % column;
        int y = i / column;

        if (x == 0)
        {
            REQUIRE((m.cells[i].connections & MazeGen::ToWest) == 0);
            REQUIRE(m.cells[i].pWest == nullptr);
        }

        if (x == column - 1)
        {
            REQUIRE((m.cells[i].connections & MazeGen::ToEast) == 0);
            REQUIRE(m.cells[i].pEast == nullptr);
        }

        if (y == 0)
        {
            REQUIRE((m.cells[i].connections & MazeGen::ToNorth) == 0);
            REQUIRE(m.cells[i].pNorth == nullptr);
        }

        if (y == row - 1)
        {
            REQUIRE((m.cells[i].connections & MazeGen::ToSouth) == 0);
            REQUIRE(m.cells[i].pSouth == nullptr);
        }
    }
}