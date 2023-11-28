#include <gtest/gtest.h>

#include <vector>

//! @brief Recursive helper to get all possible paths from node 0 to node n - 1
//! @param[in]      graph Reference to DAG of n nodes, 0 to n - 1
//! @param[out]     ans   Reference to vector of possible paths from 0 to n - 1
//! @param[in, out] curr  Reference to vector containing current path
//! @param[in]      node  Current node in DAG to process
static void backtrackFA(const std::vector<std::vector<int>>& graph,
                        std::vector<std::vector<int>>&       ans,
                        std::vector<int>&                    curr,
                        int                                  node)
{
    curr.push_back(node);

    const auto graph_size = static_cast<int>(graph.size());
    if (node == graph_size - 1)
    {
        ans.push_back(curr);
        return;
    }

    for (const int next_node : graph.at(node))
    {
        backtrackFA(graph, ans, curr, next_node);
        curr.pop_back();
    }
}

//! @brief First attempt to find all possible paths from node 0 to node n - 1
//! @param[in] graph Reference to directed acyclic graph of n nodes, 0 to n - 1
//! @return Vector of all possible paths from node 0 to node n - 1
static std::vector<std::vector<int>> allPathsSourceTargetFA(
    const std::vector<std::vector<int>>& graph)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /711/backtracking/4575/
    //!
    //!          Time complexity O(2^n * n) where n = number of nodes in graph.
    //!          Space complexity O(n) for curr and call stack

    std::vector<std::vector<int>> ans {};
    std::vector<int>              curr {};
    backtrackFA(graph, ans, curr, 0);
    return ans;
}

//! @brief Backtracking solution to find all possible paths from node 0 to n - 1
//! @param[in] graph Reference to directed acyclic graph of n nodes, 0 to n - 1
//! @return Vector of all possible paths from node 0 to node n - 1
static std::vector<std::vector<int>> allPathsSourceTargetDS1(
    const std::vector<std::vector<int>>& graph)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /711/backtracking/4575/
    //!
    //!          Time complexity O(2^n * n) where n = number of nodes in graph.
    //!          Space complexity O(n) for curr and call stack

    const int                     target {static_cast<int>(graph.size()) - 1};
    std::vector<std::vector<int>> results {};
    std::vector<int>              path {0};

    auto backtrack = [&](int currNode, std::vector<int>& path)
    {
        if (currNode == target)
        {
            results.push_back(path);
            return;
        }

        for (const int nextNode : graph[currNode])
        {
            path.push_back(nextNode);
            backtrack(nextNode, path);
            path.pop_back();
        }
    };

    backtrack(0, path);
    return results;
}

TEST(AllPathsSourceTargetTest, SampleTest1)
{
    const std::vector<std::vector<int>> graph {{1, 2}, {3}, {3}, {}};
    const std::vector<std::vector<int>> expected_output {{0, 1, 3}, {0, 2, 3}};

    EXPECT_EQ(expected_output, allPathsSourceTargetFA(graph));
    EXPECT_EQ(expected_output, allPathsSourceTargetDS1(graph));
}

TEST(AllPathsSourceTargetTest, SampleTest2)
{
    const std::vector<std::vector<int>> graph {
        {4, 3, 1}, {3, 2, 4}, {3}, {4}, {}};
    const std::vector<std::vector<int>> expected_output {
        {0, 4}, {0, 3, 4}, {0, 1, 3, 4}, {0, 1, 2, 3, 4}, {0, 1, 4}};

    EXPECT_EQ(expected_output, allPathsSourceTargetFA(graph));
    EXPECT_EQ(expected_output, allPathsSourceTargetDS1(graph));
}
