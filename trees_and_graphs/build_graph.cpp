#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>

//! @brief Example code to build a graph from a vector of edges
//! @param[in] edges Vector of vectors containing (un)directed edges
//! @return Map of neighbors for a given node
static std::unordered_map<int, std::vector<int>> buildGraph(
    std::vector<std::vector<int>> edges)
{
    std::unordered_map<int, std::vector<int>> graph;

    for (const auto& edge : edges)
    {
        const int x {edge[0]};
        const int y {edge[1]};

        graph[x].push_back(y);

        // Uncomment following line if graph is undirected
        // graph[y].push_back(x);
    }

    return graph;
}

TEST(BuildGraphTest, SampleTest)
{
    const auto graph = buildGraph({{0, 1}, {1, 2}, {2, 0}, {2, 3}});
    EXPECT_EQ(4ULL, graph.size());
    EXPECT_EQ(1ULL, graph[0].size());
    EXPECT_EQ(1ULL, graph[1].size());
    EXPECT_EQ(2ULL, graph[2].size());
    EXPECT_TRUE(graph[3].empty());
}