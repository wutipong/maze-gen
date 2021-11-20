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
        REQUIRE(ctx.GetAdjacentCell(50, Direction::North) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(48, Direction::North) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(3, Direction::North) == MazeContext::InvalidCell);
        
        REQUIRE(ctx.GetAdjacentCell(7, Direction::North) == 1);
        REQUIRE(ctx.GetAdjacentCell(47, Direction::North) == 41);
    }

    SECTION("Connect to south cell")
    {
        REQUIRE(ctx.GetAdjacentCell(50, Direction::South) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(48, Direction::South) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(42, Direction::South) == MazeContext::InvalidCell);

        REQUIRE(ctx.GetAdjacentCell(2, Direction::South) == 8);
        REQUIRE(ctx.GetAdjacentCell(30, Direction::South) == 36);
    }

    SECTION("Connect to West cell")
    {
        REQUIRE(ctx.GetAdjacentCell(50, Direction::West) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(48, Direction::West) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(0, Direction::West) == MazeContext::InvalidCell);

        REQUIRE(ctx.GetAdjacentCell(2, Direction::West) == 1);
        REQUIRE(ctx.GetAdjacentCell(35, Direction::West) == 34);
    }

    SECTION("Connect to East cell")
    {
        REQUIRE(ctx.GetAdjacentCell(50, Direction::East) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(48, Direction::East) == MazeContext::InvalidCell);
        REQUIRE(ctx.GetAdjacentCell(5, Direction::East) == MazeContext::InvalidCell);

        REQUIRE(ctx.GetAdjacentCell(2, Direction::East) == 3);
        REQUIRE(ctx.GetAdjacentCell(30, Direction::East) == 31);
    }
}