#include <gtest/gtest.h>

#include <vector>

//! @brief Find smallest set of vertices from which all nodes are reachable
//! @param[in] n     Number of vertices in directed acyclic graph
//! @param[in] edges Vector of directed edges from x to y for edges[i] = [x, y]
//! @return Vector containing smallest set of vertices
static std::vector<int> findSmallestSetOfVertices(
    int                                  n,
    const std::vector<std::vector<int>>& edges)
{
    std::vector<int> indegree(n);

    for (const auto& edge : edges)
    {
        ++indegree[edge[1]];
    }

    std::vector<int> ans {};
    for (int i = 0; i < n; ++i)
    {
        if (indegree[i] == 0)
        {
            ans.push_back(i);
        }
    }

    return ans;
}

TEST(FindSmallestSetOfVerticesTest, SampleTest)
{
    const std::vector<std::vector<int>> edges {
        {0, 1}, {0, 2}, {2, 5}, {3, 4}, {4, 2}};
    const std::vector<int> expected_output {0, 3};
    
    EXPECT_EQ(expected_output, findSmallestSetOfVertices(6, edges));
}