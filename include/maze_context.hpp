#include "maze.hpp"
#include <memory>
#include <set>
#include <vector>

namespace MazeGen
{
class MazeContext
{
  public:
    typedef std::set<size_t> Set;
    typedef std::shared_ptr<Set> SetPtr;

    struct JoinResult
    {
        size_t from;
        size_t to;
        Direction direction;
        Direction opposite;
    };

    const size_t row;
    const size_t column;
    const size_t cellCount;

  private:
    std::vector<SetPtr> disjointSets;
    int setCount;

  public:
    MazeContext(size_t column, size_t row);
    bool TryJoinSet(size_t to, size_t from);

    JoinResult RandomJoin(RandomCellFunc randomCell = RandomCellFuncImpl,
                          RandomDirectionFunc randomDirection = RandomDirectionFuncImpl);

    size_t GetAdjacentCell(size_t cell, Direction direction);

    size_t SetCount() const
    {
        return setCount;
    }
};
} // namespace MazeGen
