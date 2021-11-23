#include "maze.hpp"
#include "maze_path.hpp"

#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <catch2/catch.hpp>

using namespace MazeGen;

TEST_CASE("FindPath", "[Benchmark]")
{
    auto m = MazeGen::Generate(50, 50);

    BENCHMARK("Depth-first Search")
    {
        return MazeGen::FindPathDFS(m, 20, 2200);
    };

    BENCHMARK("Breadth-first Search")
    {
        return MazeGen::FindPathBFS(m, 20, 2200);
    };
}