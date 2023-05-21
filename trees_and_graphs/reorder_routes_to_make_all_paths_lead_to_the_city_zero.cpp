#include <gtest/gtest.h>

#include <set>
#include <unordered_map>
#include <vector>

using Graph_t = std::unordered_map<int, std::vector<int>>;

//! @brief DFS starting at node for determining number of edges to swap
//! @param[in]     node  Starting node to travel from
//! @param[in]     graph Undirected mapping of node to its neighbors
//! @param[in]     roads Set of original directed edges between nodes
//! @param[in,out] seen  Vector of nodes that have been visited
//! @return Number of edges to swap to make all paths lead to node
static int dfsRecursive(int                              node,
                        const Graph_t&                   graph,
                        const std::set<std:vector<int>>& roads,
                        std::vector<bool>&               seen)
{
    int ans {};

    for (const int neighbor : graph.at(node))
    {
        if (not seen[neighbor])
        {
            if (roads.find({node, neighbor}) != roads.end())
            {
                ++ans;
            }

            seen[neighbor] = true;
            ans += dfsRecursive(neighbor);
        }
    }

    return ans;
}

//! @brief Get min number of swaps to make all paths lead to the city zero
//! @param[in] n           Number of cities numbered from 0 to n - 1
//! @param[in] connections Roads between city x and city y
//! @return Minimum number of swaps needed so every city can reach city 0
static int minReorder(int n, const std::vector<std::vector<int>>& connections)
{
    //! @details Time complexity is O(N) because only visit each node once and
    //!          do constant work.
    //!          Space complexity is O(N) since roads, graph, and seen all use
    //!          up to O(N) space at most

    std::vector<bool>          seen(n, false);
    std::set<std::vector<int>> roads {};
    Graph_t                    graph {};

    for (const auto& edge : connections)
    {
        const int x {edge[0]};
        const int y {edge[1]};

        graph[x].push_back(y);
        graph[y].push_back(x);
        roads.emplace({x, y});
    }

    seen[0] = true;
    return dfsRecursive(0, graph, roads, seen);
}