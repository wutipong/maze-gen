#include <catch2/catch.hpp>

#include <maze.hpp>

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
        REQUIRE(ctx.GetAdjacentCell(47, MazeContext::Direction::North) == 39);
    }
}