#include <gtest/gtest.h>

#include <functional>
#include <unordered_map>
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
    //!          Every time a new node is added to the graph, the number of
    //!          paths double. For a graph with n nodes, at maximum, there could
    //!          be sum_{i = 0}_{n - 2} 2^i = 2^(n - 1) - 1 paths between the
    //!          start and end nodes. For each path, there could be at most
    //!          n - 2 intermediate nodes - it takes O(n) to build each path.
    //!          Space complexity O(n) for curr and call stack

    const int                     target {static_cast<int>(graph.size()) - 1};
    std::vector<std::vector<int>> results {};
    std::vector<int>              path {0};

    std::function<void(int, std::vector<int>&)> backtrack =
        [&](int currNode, std::vector<int>& path)
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

//! @brief Top-down DP solution to find all possible paths from node 0 to n - 1
//! @param[in] graph Reference to directed acyclic graph of n nodes, 0 to n - 1
//! @return Vector of all possible paths from node 0 to node n - 1
static std::vector<std::vector<int>> allPathsSourceTargetDS2(
    const std::vector<std::vector<int>>& graph)
{
    //! @details leetcode.com/problems/all-paths-from-source-to-target/editorial
    //!
    //!          Time complexity O(2^n * n) where n = number of nodes in graph.
    //!          There can be at most 2^(n - 1) - 1 paths. To estimate the
    //!          overall time complexity, start from last step when the starting
    //!          node is prepended to each path returned from allPathsToTarget.
    //!          Copying each path to create a new path can take up to n steps
    //!          for each final path. Therefore the last step could take
    //!          O(2^(n - 1) * n) time. Right before the last step, when the max
    //!          path length is n - 1, we have 2^(n - 2) paths. A loose upper
    //!          bound would be sum_{i=1}_{n} 2^(i - 1) * i = O(2^n * n).
    //!          A lower bound of the time complexity is O(2^n * n) following
    //!          similar logic from DS1 for an overall complexity of O(2^n * n).
    //!          Space complexity O(2^n * n), can have 2^(n - 1) - 1 paths as
    //!          the results and each path can contain up to n nodes.
    //!          The recursive call stack can grow up to n consecutive calls.
    //!          Memoizing the intermediate calls of allPathsToTarget requires
    //!          sum_{i = 1}_{n} i * 2^i = O(2^n * n).

    const auto target = static_cast<int>(graph.size()) - 1;

    std::unordered_map<int, std::vector<std::vector<int>>> memo;

    //! Get all paths from currNode to target node
    //! Recursive formula: For all nextNodes that are neighbors of currNode,
    //! allPathsToTarget(currNode) = {currNode + allPathsToTarget(nextNode)}
    std::function<std::vector<std::vector<int>>(int)> allPathsToTarget =
        [&](int currNode)
        {
            if (memo.count(currNode) > 0)
            {
                return memo[currNode];
            }

            std::vector<std::vector<int>> results;
            if (currNode == target)
            {
                results.emplace_back({target});
            }
            else
            {
                //! Iterate through neighbor nodes of current node
                for (const int nextNode : graph[currNode])
                {
                    for (const auto& path : allPathsToTarget(nextNode))
                    {
                        std::vector<int> newPath {currNode};
                        newPath.insert(newPath.end(), path.begin(), path.end());
                        results.push_back(std::move(newPath));
                    }
                }
            }

            memo[currNode] = results;
            return results;
        };

    return allPathsToTarget(0);
}

TEST(AllPathsSourceTargetTest, SampleTest1)
{
    const std::vector<std::vector<int>> graph {{1, 2}, {3}, {3}, {}};
    const std::vector<std::vector<int>> expected_output {{0, 1, 3}, {0, 2, 3}};

    EXPECT_EQ(expected_output, allPathsSourceTargetFA(graph));
    EXPECT_EQ(expected_output, allPathsSourceTargetDS1(graph));
    EXPECT_EQ(expected_output, allPathsSourceTargetDS2(graph));
}

TEST(AllPathsSourceTargetTest, SampleTest2)
{
    const std::vector<std::vector<int>> graph {
        {4, 3, 1}, {3, 2, 4}, {3}, {4}, {}};
    const std::vector<std::vector<int>> expected_output {
        {0, 4}, {0, 3, 4}, {0, 1, 3, 4}, {0, 1, 2, 3, 4}, {0, 1, 4}};

    EXPECT_EQ(expected_output, allPathsSourceTargetFA(graph));
    EXPECT_EQ(expected_output, allPathsSourceTargetDS1(graph));
    EXPECT_EQ(expected_output, allPathsSourceTargetDS2(graph));
}
