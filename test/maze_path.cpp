#include "maze.hpp"
#include "maze_path.hpp"
#include <catch2/catch.hpp>

using namespace MazeGen;

TEST_CASE("FindPathDFS", "[MazePath]")
{
    constexpr int column = 5, row = 5;
    auto m = MazeGen::Generate(column, row);

    auto path = MazeGen::FindPathDFS(m, 2, 20);

    REQUIRE(path.size() > 0);
    REQUIRE(path.front().cell == 2);
    REQUIRE(path.back().cell == 20);
}

TEST_CASE("FindPathDFS -- Same Cell", "[MazePath]")
{
    constexpr int column = 5, row = 5;
    auto m = MazeGen::Generate(column, row);

    auto path = MazeGen::FindPathDFS(m, 20, 20);

    REQUIRE(path.size() == 1);
    REQUIRE(path[0].cell == 20);
}


TEST_CASE("FindPathBFS", "[MazePath]")
{
    constexpr int column = 5, row = 5;
    auto m = MazeGen::Generate(column, row);

    auto path = MazeGen::FindPathBFS(m, 2, 20);

    REQUIRE(path.size() > 0);
    REQUIRE(path.front().cell == 2);
    REQUIRE(path.back().cell == 20);
}

TEST_CASE("FindPathBFS -- Same Cell", "[MazePath]")
{
    constexpr int column = 5, row = 5;
    auto m = MazeGen::Generate(column, row);

    auto path = MazeGen::FindPathBFS(m, 20, 20);

    REQUIRE(path.size() == 1);
    REQUIRE(path[0].cell == 20);
}