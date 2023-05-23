#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>

//! @brief Recursive helper function determines if start-to-end path exists
//! @param[in]     start Starting vertex of path
//! @param[in]     end   Ending vertex of path
//! @param[in]     graph Map of vertex to its neighbors
//! @param[in,out] seen  Vector indicating if current vertex has been visited
//! @return True if a path exists between start and end, else false
static bool dfsFA(int                                              start,
                  int                                              end,
                  const std::unordered_map<int, std::vector<int>>& graph,
                  std::vector<int>&                                seen)
{
    if (start == end)
    {
        return true;
    }

    bool path_exists {};

    for (const int neighbor : graph.at(start))
    {
        if (!seen[neighbor])
        {
            seen[neighbor] = true;

            path_exists =
                path_exists || dfsRecursive(neighbor, end, graph, seen);
        }
    }

    return path_exists;

} // static bool dfsFA( ...

//! @brief First attempt solution to determine if there is a valid path
//! @param[in] n           Number of vertices
//! @param[in] edges       Vector of bi-directional edges
//! @param[in] source      Starting vertex of path
//! @param[in] destination Ending vertex of path
//! @return True if there is a valid path between source and destination
static bool validPathFA(int                                  n,
                        const std::vector<std::vector<int>>& edges,
                        int                                  source,
                        int                                  destination)
{
    std::unordered_map<int, std::vector<int>> graph {};
    for (const auto& edge : edges)
    {
        graph[edge.front()].push_back(edge.back());
        graph[edge.back()].push_back(edge.front());
    }

    std::vector<int> seen(n, false);
    seen[source] = true;
    return dfsFA(source, destination, graph, seen);

} // static bool validPathFA( ...

TEST(ValidPathTest, SampleTest1)
{
    const std::vector<std::vector<int>> edges {{0, 1}, {1, 2}, {2, 0}};
    EXPECT_TRUE(validPathFA(3, edges, 0, 2));
}

TEST(ValidPathTest, SampleTest2)
{
    const std::vector<std::vector<int>> edges {
        {0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};
    EXPECT_FALSE(validPathFA(6, edges, 0, 5));
}