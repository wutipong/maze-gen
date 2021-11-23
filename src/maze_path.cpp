#include "maze_path.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <stack>

using namespace MazeGen;

namespace
{
Direction Next(Direction direction)
{
    switch (direction)
    {
    case Direction::Invalid:
        return Direction::North;
    case Direction::North:
        return Direction::East;
    case Direction::East:
        return Direction::South;
    case Direction::South:
        return Direction::West;
    case Direction::West:
        return Direction::Invalid;
    }

    return Direction::Invalid;
}
} // namespace

Path MazeGen::FindPathDFS(Maze &m, int from, int to)
{
    Path p;

    p.push_back(PathNode{.cell = from, .fromDirection = Direction::Invalid, .toDirection = Direction::Invalid});

    if (from == to)
    {
        return p;
    }

    while (true)
    {
        auto &currentNode = p.back();
        if (currentNode.cell == to)
            break;

        auto &cell = m.At(currentNode.cell);

        currentNode.toDirection = Next(currentNode.toDirection);
        if (currentNode.toDirection == Direction::Invalid)
        {
            p.pop_back();
            continue;
        }

        if (currentNode.toDirection == currentNode.fromDirection)
        {
            continue;
        }

        auto nextCell = cell.ConnectedCell(currentNode.toDirection);
        if (nextCell == InvalidCell)
        {
            continue;
        }

        PathNode next{.cell = m.AdjacentCellID(currentNode.cell, currentNode.toDirection),
                      .fromDirection = Opposite(currentNode.toDirection),
                      .toDirection = Direction::Invalid};

        p.push_back(next);
    }

    return p;
}

Path MazeGen::FindPathBFS(Maze &m, int from, int to)
{
    if (from == to)
    {
        Path p = {{.cell = from, .fromDirection = Direction::Invalid, .toDirection = Direction::Invalid}};
        return p;
    }

    struct SearchNode
    {
        int id;
        bool processed = false;
        Direction toDirection = Direction::Invalid;
        Direction fromDirection = Direction::Invalid;
    };

    std::map<int, SearchNode> nodeMap;
    constexpr int directionCount = static_cast<int>(Direction::Count);
    bool foundToNode = false;

    nodeMap.insert_or_assign(from, SearchNode{.id = from});
    while (!foundToNode)
    {
        for (auto &kv : nodeMap)
        {
            auto &n = kv.second;
            if (n.processed)
                continue;

            auto &cell = m.At(n.id);
            for (int i = 0; i < directionCount; i++)
            {
                const Direction direction = static_cast<Direction>(i);
                if (direction == n.fromDirection)
                    continue;

                int connectedId = cell.ConnectedCell(direction);
                if (connectedId == InvalidCell)
                    continue;

                SearchNode newNode = {.id = connectedId, .fromDirection = Opposite(direction)};
                nodeMap.insert_or_assign(connectedId, newNode);

                if (connectedId == to)
                {
                    foundToNode = true;
                    break;
                }
            }
            n.processed = true;
            if (foundToNode)
                break;
        }
    }

    Path p;
    Direction nextToDirection = Direction::Invalid;
    for (SearchNode &s = nodeMap[to]; s.id != from; s = nodeMap[m.AdjacentCellID(s.id, s.fromDirection)])
    {
        p.push_back(PathNode{.cell = s.id, .fromDirection = s.fromDirection, .toDirection = nextToDirection});
        nextToDirection = Opposite(s.fromDirection);
    }
    p.push_back(PathNode{.cell = from, .toDirection = nextToDirection});

    std::reverse(p.begin(), p.end());
    return p;
}