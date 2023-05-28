#include <gtest/gtest.h>

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Graph_t = std::unordered_map<int, std::vector<int>>;

//! @brief Recursive helper function to get number of nodes reachable from start
//! @param[in]      start Starting node
//! @param[in]      graph Reference to map of node and its connected neighbors
//! @param[in, out] seen  Reference to vector of visited nodes
//! @return Number of nodes reachable from start
static int dfsFA(int start, const Graph_t& graph, std::vector<bool>& seen)
{
    if (graph.count(start) == 0)
    {
        return 0;
    }

    int num_nodes {};

    for (const int neighbor : graph.at(start))
    {
        if (not seen[neighbor])
        {
            seen[neighbor] = true;
            num_nodes += 1 + dfsFA(neighbor, graph, seen);
        }
    }

    return num_nodes;

} // static int dfsFA( ...

//! @brief Get max nodes you can reach from 0 without visiting a restricted node
//! @param[in] n          Number of nodes in undirected tree
//! @param[in] edges      2D vector of length n - 1 where edges[i] = [a_i, b_i]
//! @param[in] restricted Vector of restricted nodes
//! @return Max number of nodes can reach from node 0 while avoiding restricted
static int reachableNodesFA(int                                  n,
                            const std::vector<std::vector<int>>& edges,
                            const std::vector<int>&              restricted)
{
    std::unordered_set<int> avoid(restricted.cbegin(), restricted.cend());

    Graph_t graph {};
    for (const auto& edge : edges)
    {
        const int node1 {edge.front()};
        const int node2 {edge.back()};
        if (avoid.count(node1) > 0 || avoid.count(node2) > 0)
        {
            continue;
        }

        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }

    std::vector<bool> seen(n, false);
    seen[0] = true;

    return 1 + dfsFA(0, graph, seen);

} // static int reachableNodesFA( ...

//! @brief Get max nodes you can reach from 0 without visiting a restricted node
//! @param[in] n          Number of nodes in undirected tree
//! @param[in] edges      2D vector of length n - 1 where edges[i] = [a_i, b_i]
//! @param[in] restricted Vector of restricted nodes
//! @return Max number of nodes can reach from node 0 while avoiding restricted
static int reachableNodesBFS(int                                  n,
                             const std::vector<std::vector<int>>& edges,
                             const std::vector<int>&              restricted)
{
    //! @details https://leetcode.com/problems/reachable-nodes-with-restrictions
    //!          /editorial/
    //!
    //!          Time complexity O(N) where N is the number of nodes in tree.
    //!          In a typical BFS search, the time complexity is O(V + E) where
    //!          V is the number of vertices and E is the number of edges. In
    //!          this problem, there are n nodes and n - 1 edges.
    //!          Space complexity O(N). Since the number of edges and vertices
    //!          are of the same order of magnitude, we used a hash map
    //!          neighbors rather than an adjacency matrix to store the edges.
    //!          This costs O(N) space for O(N) edges. We also use seen to
    //!          record the visited nodes which takes O(N) space. There may be
    //!          up to N nodes in queue which takes O(N) space.

    //! Stores all edges in neighbors
    std::vector<std::vector<int>> neighbors(n);
    for (const auto& edge : edges)
    {
        const int nodeA {edge.front()};
        const int nodeB {edge.back()};

        neighbors[nodeA].push_back(nodeB);
        neighbors[nodeB].push_back(nodeA);
    }

    //! Mark the nodes in restricted as visited
    std::vector<bool> seen(n);
    for (const int node : restricted)
    {
        seen[node] = true;
    }

    //! Store all the nodes to be visited in bfsQueue
    int ans {};

    std::queue<int> bfsQueue({0});
    seen[0] = true;

    while (not bfsQueue.empty())
    {
        const int currNode {bfsQueue.front()};
        bfsQueue.pop();
        ++ans;

        //! For all neighbors of the current node, if we haven't visited it
        //! before, add it to bfsQueue and mark it as visited
        for (const auto nextNode : neighbors[currNode])
        {
            if (not seen[nextNode])
            {
                seen[nextNode] = true;
                bfsQueue.push(nextNode);
            }
        }
    }

    return ans;

} // static int reachableNodesBFS( ...

TEST(ReachableNodesTest, SampleTest0)
{
    const std::vector<std::vector<int>> edges {
        {0, 1}, {1, 2}, {3, 1}, {4, 0}, {0, 5}, {5, 6}};
    const std::vector<int> restricted {4, 5};

    EXPECT_EQ(4, reachableNodesFA(7, edges, restricted));
    EXPECT_EQ(4, reachableNodesBFS(7, edges, restricted));
}

TEST(ReachableNodesTest, SampleTest1)
{
    const std::vector<std::vector<int>> edges {
        {0, 1}, {0, 2}, {0, 5}, {0, 4}, {3, 2}, {6, 5}};
    const std::vector<int> restricted {4, 2, 1};

    EXPECT_EQ(3, reachableNodesFA(7, edges, restricted));
    EXPECT_EQ(3, reachableNodesBFS(7, edges, restricted));
}

TEST(ReachableNodesTest, SimpleTest)
{
    const std::vector<std::vector<int>> edges {{0, 1}};
    const std::vector<int> restricted {1};

    EXPECT_EQ(1, reachableNodesFA(2, edges, restricted));
    EXPECT_EQ(1, reachableNodesBFS(2, edges, restricted));
}