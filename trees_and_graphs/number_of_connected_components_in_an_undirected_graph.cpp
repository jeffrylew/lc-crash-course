#include <gtest/gtest.h>

#include <numeric>
#include <stack>
#include <unordered_map>
#include <vector>

//! @brief First attempt solution to get number of connected components in graph
//! @param[in] n     Number of nodes in graph
//! @param[in] edges Vector of connected nodes where edges[i] = [a_i, b_i]
//! @return Number of connected components in an undirected graph
static int countComponentsFA(int n, const std::vector<std::vector<int>>& edges)
{
    int ncomponents {};

    std::unordered_map<int, std::vector<int>> graph {};
    for (const auto& edge : edges)
    {
        graph[edge.front()].push_back(edge.back());
        graph[edge.back()].push_back(edge.front());
    }

    std::stack<int>   stack {};
    std::vector<bool> seen(n);

    //! Test cases assume 0 is present so start with it
    for (int vertex = 0; vertex < n; ++vertex)
    {
        if (seen[vertex])
        {
            //! Already processed node, skip to next one
            continue;
        }
        
        ++ncomponents;
        seen[vertex] = true;
        stack.push(vertex);

        while (not stack.empty())
        {
            const int node {stack.top()};
            stack.pop();

            for (const int neighbor : graph[node])
            {
                if (not seen[neighbor])
                {
                    seen[neighbor] = true;
                    stack.push(neighbor);
                }
            }
        }
    }

    return ncomponents;

} // static int countComponentsFA( ...

static void dfsRecursive(std::vector<int>   adjList[],
                         std::vector<bool>& visited,
                         int                src)
{
    visited[src] = true;

    for (const int neighbor : adjList[src])
    {
        if (not visited[neighbor])
        {
            dfsRecursive(adjList, visited, neighbor);
        }
    }

} // static void dfsRecursive( ...

//! @brief Recursive DFS solution to get number of connected components in graph
//! @param[in] n     Number of nodes in graph
//! @param[in] edges Vector of connected nodes where edges[i] = [a_i, b_i]
//! @return Number of connected components in an undirected graph
static int countComponentsDFS(int n, const std::vector<std::vector<int>>& edges)
{
    //! @details https://leetcode.com/problems/
    //!          number-of-connected-components-in-an-undirected-graph/editorial
    //!
    //!          Time complexity O(V + E) where V = number of vertices and
    //!          E = number of edges. Building the adjacency list will take O(E)
    //!          operations since we iterate over the list of edges once and
    //!          insert each edge into two lists. During DFS traversal, each
    //!          vertex will only be visited once since we mark each as visited
    //!          as soon as we see it. Also, we look at each edge once when we
    //!          iterate over the edge list of each vertex.
    //!          Space complexity O(V + E). Building the adjacency list takes
    //!          O(E) space. A vector of size O(V) is needed to keep track of
    //!          visited vertices. Also, the run-time stack for DFS uses O(V).

    if (n == 0)
    {
        return 0;
    }

    int               components {};
    std::vector<bool> visited(n, false);
    std::vector<int>  adjList[n];

    for (const auto& edge : edges)
    {
        adjList[edge.at(0)].push_back(edge.at(1));
        adjList[edge.at(1)].push_back(edge.at(0));
    }

    for (int i = 0; i < n; ++i)
    {
        if (not visited[i])
        {
            ++components;
            dfsRecursive(adjList, visited, i);
        }
    }

    return components;

} // static int countComponentsDFS( ...

static int find(std::vector<int>& representative, int vertex)
{
    if (vertex == representative[vertex])
    {
        return vertex;
    }

    return
        representative[vertex] = find(representative, representative[vertex]);
}

static int combine(std::vector<int>& representative,
                   std::vector<int>& size,
                   int               vertex1,
                   int               vertex2)
{
    vertex1 = find(representative, vertex1);
    vertex2 = find(representative, vertex2);

    if (vertex1 == vertex2)
    {
        return 0;
    }
    else
    {
        if (size[vertex1] > size[vertex2])
        {
            size[vertex1] += size[vertex2];
            representative[vertex2] = vertex1;
        }
        else
        {
            size[vertex2] += size[vertex1];
            representative[vertex1] = vertex2;
        }
        return 1;
    }

} // static int combine( ...

//! @brief Disjoint Set Union solution to get number of connected components
//! @param[in] n     Number of nodes in graph
//! @param[in] edges Vector of connected nodes where edges[i] = [a_i, b_i]
//! @return Number of connected components in an undirected graph
static int countComponentsDSU(int n, const std::vector<std::vector<int>>& edges)
{
    //! @details Time complexity O(E * alpha(n)) where E = number of edges and
    //!          alpha(n) is the inverse Ackermann function. Iterating over each
    //!          edge requires O(E) operations and for every operation we
    //!          perform the combine method which is O(alpha(n)).
    //!          Space complexity O(V) where V = number of vertices. Storing the
    //!          representative/immediate parent of each vertex takes O(V) space
    //!          and storing the size of components takes O(V) space.

    std::vector<int> representative(n);
    std::vector<int> size(n, 1);

    std::iota(representative.begin(), representative.end(), 0);

    int components {n};

    for (const auto& edge : edges)
    {
        components -= combine(representative, size, edge.at(0), edge.at(1));
    }

    return components;

} // static int countComponentsDSU( ...

TEST(CountComponentsTest, SampleTest1)
{
    const std::vector<std::vector<int>> edges {{0, 1}, {1, 2}, {3, 4}};
    
    EXPECT_EQ(2, countComponentsFA(5, edges));
    EXPECT_EQ(2, countComponentsDFS(5, edges));
    EXPECT_EQ(2, countComponentsDSU(5, edges));
}

TEST(CountComponentsTest, SampleTest2)
{
    const std::vector<std::vector<int>> edges {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    
    EXPECT_EQ(1, countComponentsFA(5, edges));
    EXPECT_EQ(1, countComponentsDFS(5, edges));
    EXPECT_EQ(1, countComponentsDSU(5, edges));
}

TEST(CountComponentsTest, TrickTest3)
{
    const std::vector<std::vector<int>> edges {{2, 3}, {1, 2}, {1, 3}};
    
    EXPECT_EQ(2, countComponentsFA(4, edges));
    EXPECT_EQ(2, countComponentsDFS(4, edges));
    EXPECT_EQ(2, countComponentsDSU(4, edges));
}
