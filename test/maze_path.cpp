#include "maze.hpp"
#include "maze_path.hpp"
#include <catch2/catch.hpp>
#include <iostream>

using namespace MazeGen;
TEST_CASE("FindPath", "[MazePath]")
{
    constexpr size_t column = 5, row = 5;
    auto m = MazeGen::Generate(column, row);

    auto path = MazeGen::FindPath(m, 2, 20);

    REQUIRE(path.size() > 0);
}