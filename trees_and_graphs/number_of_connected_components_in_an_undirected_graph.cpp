#include <gtest/gtest.h>

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

TEST(CountComponentsTest, SampleTest1)
{
    const std::vector<std::vector<int>> edges {{0, 1}, {1, 2}, {3, 4}};
    
    EXPECT_EQ(2, countComponentsFA(5, edges));
}

TEST(CountComponentsTest, SampleTest2)
{
    const std::vector<std::vector<int>> edges {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    
    EXPECT_EQ(1, countComponentsFA(5, edges));
}

TEST(CountComponentsTest, TrickTest3)
{
    const std::vector<std::vector<int>> edges {{2, 3}, {1, 2}, {1, 3}};
    
    EXPECT_EQ(2, countComponentsFA(4, edges));
}
