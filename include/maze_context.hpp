#pragma once

#include "maze.hpp"
#include <memory>
#include <set>
#include <vector>

namespace MazeGen
{
class MazeContext
{
  public:
    typedef std::set<int> Set;
    typedef std::shared_ptr<Set> SetPtr;

    struct JoinResult
    {
        int from;
        int to;
        Direction direction;
        Direction opposite;
    };

    const int row;
    const int column;
    const int cellCount;

  private:
    std::vector<SetPtr> disjointSets;
    int setCount;

  public:
    MazeContext(int column, int row);
    bool TryJoinSet(int to, int from);

    JoinResult RandomJoin(RandomCellFunc randomCell = RandomCellFuncImpl,
                          RandomDirectionFunc randomDirection = RandomDirectionFuncImpl);

    int GetAdjacentCell(int cell, Direction direction);

    int SetCount() const
    {
        return setCount;
    }
};
} // namespace MazeGen
