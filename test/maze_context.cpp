#include <catch2/catch.hpp>

#include <maze.hpp>
#include "maze_context.hpp"

using namespace MazeGen;

TEST_CASE("GetAdjacentCell", "[MazeContext]")
{
    MazeContext ctx{6, 8};
    REQUIRE(ctx.column == 6);
    REQUIRE(ctx.row == 8);
    REQUIRE(ctx.cellCount == 48);

    SECTION("Connect to north cell")
    {
        REQUIRE(ctx.GetAdjacentCell(50, MazeContext::Direction::North) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(48, MazeContext::Direction::North) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(3, MazeContext::Direction::North) == MazeContext::InvalidCell);
        
        REQUIRE(ctx.GetAdjacentCell(7, MazeContext::Direction::North) == 1);
        REQUIRE(ctx.GetAdjacentCell(47, MazeContext::Direction::North) == 41);
    }

    SECTION("Connect to south cell")
    {
        REQUIRE(ctx.GetAdjacentCell(50, MazeContext::Direction::South) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(48, MazeContext::Direction::South) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(42, MazeContext::Direction::South) == MazeContext::InvalidCell);

        REQUIRE(ctx.GetAdjacentCell(2, MazeContext::Direction::South) == 8);
        REQUIRE(ctx.GetAdjacentCell(30, MazeContext::Direction::South) == 36);
    }

    SECTION("Connect to West cell")
    {
        REQUIRE(ctx.GetAdjacentCell(50, MazeContext::Direction::West) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(48, MazeContext::Direction::West) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(0, MazeContext::Direction::West) == MazeContext::InvalidCell);

        REQUIRE(ctx.GetAdjacentCell(2, MazeContext::Direction::West) == 1);
        REQUIRE(ctx.GetAdjacentCell(35, MazeContext::Direction::West) == 34);
    }

    SECTION("Connect to East cell")
    {
        REQUIRE(ctx.GetAdjacentCell(50, MazeContext::Direction::East) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(48, MazeContext::Direction::East) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(5, MazeContext::Direction::East) == MazeContext::InvalidCell);

        REQUIRE(ctx.GetAdjacentCell(2, MazeContext::Direction::East) == 3);
        REQUIRE(ctx.GetAdjacentCell(30, MazeContext::Direction::East) == 31);
    }
}