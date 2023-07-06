#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

//! @brief Get max number of bombs that can be detonated from only one bomb
//! @param[in] bombs Reference to vector of [x_i, y_i, r_i] for bombs[i]
//! @return Max number of bombs that can be detonated from only one bomb
static int maximumDetonationFA(const std::vector<std::vector<int>>& bombs)
{
    //! <vector of neighboring bomb indices that are in range of ith bomb>
    std::vector<std::vector<int>> neighbors(bombs.size());

    const auto nbombs = static_cast<int>(bombs.size());

    for (int j = 0; j < nbombs; ++j)
    {
        const auto& xyr1 = bombs.at(j);

        for (int i = j + 1; i < nbombs; ++i)
        {
            const auto& xyr2 = bombs.at(i);
            const auto  dx   = static_cast<double>(xyr2.at(0) - xyr1.at(0));
            const auto  dy   = static_cast<double>(xyr2.at(1) - xyr1.at(1));

            const double dist {
                std::sqrt(std::pow(dx, 2.0) + std::pow(dy, 2.0))};
            
            if (dist <= xyr1.back())
            {
                neighbors[j].push_back(i);
            }

            if (dist <= xyr2.back())
            {
                neighbors[i].push_back(j);
            }
        }
    }

    int max_bombs {};

    for (int i = 0; i < nbombs; ++i)
    {
        int curr_bombs {};

        std::queue<int> queue({i});

        std::vector<bool> seen(bombs.size());
        seen[i] = true;

        while (not queue.empty())
        {
            const auto bomb_idx = queue.front();
            queue.pop();

            max_bombs = std::max(max_bombs, ++curr_bombs);

            for (const auto neighbor : neighbors[bomb_idx])
            {
                if (not seen[neighbor])
                {
                    seen[neighbor] = true;

                    queue.push(neighbor);
                }
            }
        }
    }

    return max_bombs;

} // static int maximumDetonationFA( ...

//! @brief Helper function to find number of reachable nodes from curr_node
//! @param[in]      curr_node Current node/bomb index
//! @param[in, out] visited   Reference to set of visited nodes
//! @param[in, out] graph     Reference to map of neighboring nodes
//! @return Number of reachable nodes from curr_node
static int dfsRecursive(int                                        curr_node,
                        std::unordered_set<int>&                   visited,
                        std::unordered_map<int, std::vector<int>>& graph)
{
    visited.insert(curr_node);

    int count {1};

    for (const int neighbor : graph[curr_node])
    {
        if (visited.count(neighbor) == 0)
        {
            count += dfsRecursive(neighbor, visited, graph);
        }
    }

    return count;
}

//! @brief Helper function to find number of reachable nodes from curr_node
//! @param[in]      curr_node Current node/bomb index
//! @param[in, out] graph     Reference to map of neighboring nodes
//! @return Number of reachable nodes from curr_node
static int dfsIterative(int                                        curr_node,
                        std::unordered_map<int, std::vector<int>>& graph)
{
    std::stack<int>         stack({curr_node});
    std::unordered_set<int> visited {curr_node};

    while (not stack.empty())
    {
        const int node = stack.top();
        stack.pop();

        for (const int neighbor : graph[node])
        {
            if (visited.count(neighbor) == 0)
            {
                visited.insert(neighbor);
                stack.push(neighbor);
            }
        }
    }

    return static_cast<int>(visited.size());
}

//! @brief Get max number of bombs that can be detonated from only one bomb
//! @param[in] bombs Reference to vector of [x_i, y_i, r_i] for bombs[i]
//! @return Max number of bombs that can be detonated from only one bomb
static int maximumDetonationDFS(const std::vector<std::vector<int>>& bombs)
{
    //! @details leetcode.com/problems/detonate-the-maximum-bombs/editorial
    //!
    //!          Time complexity O(N^3) where N = number of bombs. There are N
    //!          nodes and at most N^2 edges in the equivalence graph. Building
    //!          the graph takes O(N^2) time. Typical DFS takes O(V + E) where
    //!          V = number of nodes = N and E = number of edges = N^2. Each
    //!          node is visited once which takes O(N) time. For each node, may
    //!          need to explore N - 1 edges to find all neighbors. Since there
    //!          are N nodes, the total number of edges is N(N - 1) = O(N^2).
    //!          Space complexity O(N^2). There are O(N^2) edges stored in graph
    //!          and need to maintain hash set that contains at most N visited
    //!          nodes. The call stack of dfs contains N space.

    std::unordered_map<int, std::vector<int>> graph {};

    const auto n = static_cast<int>(bombs.size());

    //! Build the graph
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            const int xi {bombs.at(i).at(0)};
            const int yi {bombs.at(i).at(1)};
            const int ri {bombs.at(i).at(2)};

            const int xj {bombs.at(j).at(0)};
            const int yj {bombs.at(j).at(1)};
            const int rj {bombs.at(j).at(2)};

            const long dx2 {static_cast<long>(xi - xj) * (xi - xj)};
            const long dy2 {static_cast<long>(yi - yj) * (yi - yj)};
            const long ri2 {static_cast<long>(ri) * ri};
            const long rj2 {static_cast<long>(rj) * rj};

            if (ri2 >= dx2 + dy2)
            {
                graph[i].push_back(j);
            }

            if (rj2 >= dx2 + dy2)
            {
                graph[j].push_back(i);
            }
        }
    }

    int answer {};

    for (int i = 0; i < n; ++i)
    {
        /**
         * Recursive DFS
         * 
        std::unordered_set<int> visited {};

        answer = std::max(answer, dfsRecursive(i, visited, graph));
         */

        answer = std::max(answer, dfsIterative(i, graph));
    }

    return answer;

} // static int maximumDetonationDFSRecursive( ...

TEST(MaximumDetonationTest, SampleTest1)
{
    const std::vector<std::vector<int>> bombs {{2, 1, 3}, {6, 1, 4}};

    EXPECT_EQ(2, maximumDetonationFA(bombs));
    EXPECT_EQ(2, maximumDetonationDFS(bombs));
}

TEST(MaximumDetonationTest, SampleTest2)
{
    const std::vector<std::vector<int>> bombs {{1, 1, 5}, {10, 10, 5}};

    EXPECT_EQ(1, maximumDetonationFA(bombs));
    EXPECT_EQ(1, maximumDetonationDFS(bombs));
}

TEST(MaximumDetonationTest, SampleTest3)
{
    const std::vector<std::vector<int>> bombs {
        {1, 2, 3}, {2, 3, 1}, {3, 4, 2}, {4, 5, 3}, {5, 6, 4}};

    EXPECT_EQ(5, maximumDetonationFA(bombs));
    EXPECT_EQ(5, maximumDetonationDFS(bombs));
}
