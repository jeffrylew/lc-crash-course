#include <gtest/gtest.h>

#include <stack>
#include <unordered_map>
#include <vector>

static int dfs_recursive(int                                              node,
                         std::vector<bool>&                               seen,
                         const std::unordered_map<int, std::vector<int>>& graph)
{
    if (graph.count(node) == 0)
    {
        return;
    }

    for (const int neighbor : graph.at(node))
    {
        if (not seen[neighbor])
        {
            //! The next line is needed to prevent cycles
            seen[neighbor] = true;
            dfs(neighbor, seen, graph);
        }
    }
}

static int dfs_iterative(int                                              node,
                         std::vector<bool>&                               seen,
                         const std::unordered_map<int, std::vector<int>>& graph)
{
    //! @details Time complexity for DFS on graphs is usually O(N + E) where N
    //!          is the number of nodes and E is the number of edges. Each node
    //!          is visited once so a node's edges can only be iterated over
    //!          once. In the worst case scenario where every node is connected
    //!          to every other node, E = N^2.
    //!
    //!          In this problem, the time complexity is O(N^2) because the
    //!          input is given as an adjacency matrix so always need O(N^2) to
    //!          build hash map. E is dominated by N^2 because O(E < N^2) so it
    //!          is ignored.
    //!
    //!          When building graph, edges are stored in vectors. Therefore the
    //!          space complexity is O(N + E). For this problem, the complexity
    //!          isn't O(N^2) because E is not necessarily dominated by N. In
    //!          the worst case scenario E = N^2 but E is still independent of N
    //!          In the time complexity analysis, always iterate over entire
    //!          matrix to build the graph but in terms of space complexity, the
    //!          hash map only grows if the edges exist. We are using O(N) space
    //!          to build seen but this does not change the complexity.

    if (graph.count(node) == 0)
    {
        return;
    }

    std::stack<int> stack {};
    stack.push(node);

    while (not stack.empty())
    {
        int node = stack.top();
        stack.pop();

        for (const int neighbor : graph.at(node))
        {
            if (not seen[neighbor])
            {
                //! The next line is needed to prevent cycles
                seen[neighbor] = true;
                stack.push(neighbor);
            }
        }
    }
}

//! @brief Find number of provinces among n cities
//! @param[in] isConnected n x n matrix where isConnected[i][j] = 1 if connected
//! @return Total number of provinces
static int findCircleNum(std::vector<std::vector<int>> isConnected)
{
    std::unordered_map<int, std::vector<int>> graph {};

    std::vector<bool> seen(isConnected.size(), false);

    const auto n = static_cast<int>(isConnected.size());

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (isConnected[i][j] == 1)
            {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    int ans {};
    for (int i = 0; i < n; ++i)
    {
        if (not seen[i])
        {
            //! Add all nodes of a connected component to the set
            ++ans;
            seen[i] = true;
            dfs_recursive(i, seen, graph);
            // or
            // dfs_iterative(i, seen, graph);
        }
    }

    return ans;

} // static int findCircleNum( ...

TEST(FindCircleNumTest, SampleTest)
{
    EXPECT_EQ(2, findCircleNum({{1, 1, 0}, {1, 1, 0}, {0, 0, 1}}));

    EXPECT_EQ(3, findCircleNum({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}));
}