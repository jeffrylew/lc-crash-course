#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>

static int dfs_recursive(int                                        node,
                         std::vector<bool>&                         seen,
                         std::unordered_map<int, std::vector<int>>& graph)
{
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
            dfs(i, seen, graph);
        }
    }

    return ans;

} // static int findCircleNum( ...

TEST(FindCircleNumTest, SampleTest)
{
    EXPECT_EQ(2, findCircleNum({{1, 1, 0}, {1, 1, 0}, {0, 0, 1}}));

    EXPECT_EQ(3, findCircleNum({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}));
}