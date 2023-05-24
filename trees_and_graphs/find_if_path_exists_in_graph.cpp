#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <queue>
#include <stack>
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

//! @brief Breadth First Search solution to determine if there is a valid path
//! @param[in] n           Number of vertices
//! @param[in] edges       Vector of bi-directional edges
//! @param[in] source      Starting vertex of path
//! @param[in] destination Ending vertex of path
//! @return True if there is a valid path between source and destination
static bool validPathBFS(int                                  n,
                         const std::vector<std::vector<int>>& edges,
                         int                                  source,
                         int                                  destination)
{
    //! @details https://leetcode.com/problems/find-if-path-exists-in-graph/
    //!          editorial/
    //!
    //!          Time complexity O(N + E) where N = number of nodes and
    //!          E = number of edges. Building a list of adjacent edges in graph
    //!          takes O(E). Each node is pushed and popped from the queue which
    //!          takes O(N) to handle all nodes.
    //!          Space complexity O(N + E). Used a hash map graph to store all
    //!          edges, which requires O(E) space. Used seen vector to record
    //!          visited nodes, which requires O(N) space. There may be up to N
    //!          nodes stored in queue, requiring O(N) space.

    //! Store all edges in 'graph'
    std::unordered_map<int, std::vector<int>> graph {};
    for (const auto& edge : edges)
    {
        const int a {edge.front()};
        const int b {edge.back()};
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    //! Store all the nodes to be visited in 'bfsQueue'
    std::vector<bool> seen(n);
    seen[source] = true;

    std::queue<int> bfsQueue {};
    bfsQueue.push(source);

    while (not bfsQueue.empty())
    {
        const int currNode {bfsQueue.front()};
        bfsQueue.pop();

        if (currNode == destination)
        {
            return true;
        }

        for (const int nextNode : graph[currNode])
        {
            if (not seen[nextNode])
            {
                seen[nextNode] = true;
                bfsQueue.push(nextNode);
            }
        }
    }

    return false;

} // static bool validPathBFS( ...

//! @brief Recursive DFS to determine if currNode can reach destination
//! @param[in]     graph       Map of vertex to its neighbors
//! @param[in,out] seen        Vector containing visited vertices
//! @param[in]     currNode    Starting vertex of path
//! @param[in]     destination Ending vertex of path
//! @return True if a path exists between currNode and destination, else false
static bool dfsRecursive(
    const std::unordered_map<int, std::vector<int>>& graph,
    std::vector<bool>&                               seen,
    int                                              currNode,
    int                                              destination)
{
    if (currNode == destination)
    {
        return true;
    }

    if (not seen[currNode])
    {
        seen[currNode] = true;

        for (const int nextNode : graph.at(currNode))
        {
            if (dfsRecursive(graph, seen, nextNode, destination))
            {
                return true;
            }
        }
    }

    return false;

} // static bool dfsRecursive( ...

//! @brief Recursive Depth First Search solution
//! @param[in] n           Number of vertices
//! @param[in] edges       Vector of bi-directional edges
//! @param[in] source      Starting vertex of path
//! @param[in] destination Ending vertex of path
//! @return True if there is a valid path between source and destination
static bool validPathRDFS(int                                  n,
                          const std::vector<std::vector<int>>& edges,
                          int                                  source,
                          int                                  destination)
{
    //! @details Time complexity O(N + E)
    //!          Space complexity O(N + E)

    std::unordered_map<int, std::vector<int>> graph {};
    for (const auto& edge : edges)
    {
        const int a {edge.front()};
        const int b {edge.back()};
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::vector<bool> seen(n);
    return dfsRecursive(graph, seen, source, destination);

} // static bool validPathRDFS( ...

//! @brief Iterative Depth First Search solution
//! @param[in] n           Number of vertices
//! @param[in] edges       Vector of bi-directional edges
//! @param[in] source      Starting vertex of path
//! @param[in] destination Ending vertex of path
//! @return True if there is a valid path between source and destination
static bool validPathIDFS(int                                  n,
                          const std::vector<std::vector<int>>& edges,
                          int                                  source,
                          int                                  destination)
{
    //! @details Time complexity O(N + E)
    //!          Space complexity O(N + E)

    //! Store all edges according to nodes in 'graph'
    std::unordered_map<int, std::vector<int>> graph {};
    for (const auto& edge : edges)
    {
        const int a {edge.front()};
        const int b {edge.back()};
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::vector<bool> seen(n);
    seen[source] = true;

    std::stack<int> dfsStack({source});
    while (not dfsStack.empty())
    {
        const int currNode {dfsStack.top()};
        dfsStack.pop();

        if (currNode == destination)
        {
            return true;
        }

        for (const int nextNode : graph[currNode])
        {
            if (not seen[nextNode])
            {
                seen[nextNode] = true;
                dfsStack.push(nextNode);
            }
        }
    }

    return false;

} // static bool validPathIDFS( ...

class UnionFind
{
    //! Root of node i
    std::vector<int> root {};

    //! Group size of node i
    std::vector<int> rank {};

public:
    //! @brief Each node i initialized with distinct root and group size of 1 
    UnionFind(int n)
        : root(n)
        , rank(n, 1)
    {
        //! e.g. if n = 5 then root = {0, 1, 2, 3, 4}
        std::iota(root.begin(), root.end(), 0);
    }

    //! @brief Find root of the node x
    int find(int x)
    {
        if (x != root[x])
        {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    //! @brief Modify smaller group root as root of the larger group
    void join(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
            {
                std::swap(rootX, rootY);
            }

            //! Modify the root of the smaller group as the root of the larger
            //! group, also increment the size of the larger group
            root[rootX] = rootY;
            rank[rootY] += rank[rootX];
        }
    }
};

//! @brief Disjoint Set Union solution
//! @param[in] n           Number of vertices
//! @param[in] edges       Vector of bi-directional edges
//! @param[in] source      Starting vertex of path
//! @param[in] destination Ending vertex of path
//! @return True if there is a valid path between source and destination
static bool validPathDSU(int                                  n,
                         const std::vector<std::vector<int>>& edges,
                         int                                  source,
                         int                                  destination)
{
    //! @details Time complexity O(E * a(N)) where N = number of nodes and
    //!          E = number of edges. This is the amortized complexity for
    //!          performing E union find operations where a() is the inverse
    //!          Ackermann Function.
    //!          Space complexity O(N). Used two vectors root and rank to save
    //!          the root and rank of each node in the DSU data structure, with
    //!          each using O(N) space.

    UnionFind uf {n};

    for (const auto& edge : edges)
    {
        uf.join(edge.front(), edge.back());
    }

    return uf.find(source) == uf.find(destination);
}

TEST(ValidPathTest, SampleTest1)
{
    const std::vector<std::vector<int>> edges {{0, 1}, {1, 2}, {2, 0}};
    EXPECT_TRUE(validPathFA(3, edges, 0, 2));
    EXPECT_TRUE(validPathBFS(3, edges, 0, 2));
    EXPECT_TRUE(validPathRDFS(3, edges, 0, 2));
    EXPECT_TRUE(validPathIDFS(3, edges, 0, 2));
    EXPECT_TRUE(validPathDSU(3, edges, 0, 2));
}

TEST(ValidPathTest, SampleTest2)
{
    const std::vector<std::vector<int>> edges {
        {0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};
    EXPECT_FALSE(validPathFA(6, edges, 0, 5));
    EXPECT_FALSE(validPathBFS(6, edges, 0, 5));
    EXPECT_FALSE(validPathRDFS(6, edges, 0, 5));
    EXPECT_FALSE(validPathIDFS(6, edges, 0, 5));
    EXPECT_FALSE(validPathDSU(6, edges, 0, 5));
}