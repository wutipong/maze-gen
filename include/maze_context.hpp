#include <set>
#include <memory>
#include <vector>


namespace MazeGen
{

class MazeContext
{
  public:
    enum class Direction
    {
        North,
        South,
        East,
        West,
        Count,
    };

    typedef std::set<size_t> Set;
    typedef std::shared_ptr<Set> SetPtr;
    typedef size_t (*RandomCellFunc)(size_t maxCell);
    typedef Direction (*RandomDirectionFunc)();

    struct JoinResult
    {
        size_t from;
        size_t to;
        Direction direction;
    };

    static constexpr size_t InvalidCell = -1;

    const size_t row;
    const size_t column;
    const size_t cellCount;

  private:
    std::vector<SetPtr> disjointSets;
    int setCount;

  public:
    static size_t RandomCellFuncImpl(size_t maxCell);
    static Direction RandomDirectionFuncImpl();

    MazeContext(size_t column, size_t row);
    bool TryJoinSet(size_t to, size_t from);

    JoinResult RandomJoin(RandomCellFunc randomCell = RandomCellFuncImpl,
                          RandomDirectionFunc randomDirection = RandomDirectionFuncImpl);

    size_t GetAdjacentCell(size_t cell, Direction direction);
};
} // namespace MazeGen