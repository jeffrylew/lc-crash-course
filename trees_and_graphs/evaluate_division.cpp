#include <gtest/gtest.h>

#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

//! Hash map where each node maps to another hash map containing input relations
//! Edges are provided in equations and weights are provided in values
//! (weight is a value associated with an edge)
using Graph_t =
    std::unordered_map<std::string_view,
                       std::unordered_map<std::string_view, double>>;

static double answerQuery(std::string_view start,
                          std::string_view end,
                          const Graph_t&   graph)
{
    //! No info on this node/numerator/denominator
    if (graph.find(start) == graph.cend())
    {
        return -1;
    }

    std::unordered_set<std::string_view>            seen({start});
    std::stack<std::pair<std::string_view, double>> stack(
        {std::make_pair(start, 1)}); // <numerator, current ratio/multiplier>
    
    while (not stack.empty())
    {
        //! Each node is a possible denominator
        const auto [node, ratio] = stack.top();
        stack.pop();

        if (node == end)
        {
            return ratio;
        }

        for (const auto [neighbor, val] : graph.at(node))
        {
            if (seen.find(neighbor) == seen.cend())
            {
                seen.insert(neighbor);
                stack.emplace(neighbor, ratio * val);
            }
        }
    }

    return -1;

} // static double answerQuery( ...

//! @brief Get answer vector where answer[i] is answer to ith query
//! @param[in] equations Vector where equations[i] = [x, y]
//! @param[in] values    Vector where values[i] = x / y
//! @param[in] queries   Vector where queries[i] = [a, b] for a / b
static std::vector<double> calcEquation(
    const std::vector<std::vector<std::string>>& equations,
    const std::vector<double>&                   values,
    const std::vector<std::vector<std::string>>& queries)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /707/traversals-trees-graphs/4635/
    //!
    //!          Time complexity O(Q * (N + E)) where Q = queries.size(),
    //!          N = number of variables in equations (in the worst case, linear
    //!          with equations.size()), and E = number of edges. Each call to
    //!          answerQuery is a traversal on the graph we built, which costs
    //!          the number of nodes N plus the number of edges E. We perform Q
    //!          traversals.
    //!          Space complexity O(N + E) if not counting the space used for
    //!          the output. Needed to build graph, seen, and the stack.

    Graph_t graph {};

    for (int i = 0; i < static_cast<int>(equations.size()); i++)
    {
        const std::string_view numerator {equations.at(i).front()};
        const std::string_view denominator {equations.at(i).back()};
        const double           val {values.at(i)}; // numerator / denominator

        graph[numerator][denominator] = val;
        graph[denominator][numerator] = 1 / val;
    }

    std::vector<double> ans {};
    for (const auto& query : queries)
    {
        ans.push_back(answerQuery(query.front(), query.back(), graph));
    }

    return ans;

} // static std::vector<double> calcEquation( ...

TEST(CalcEquationTest, SampleTest1)
{
    const std::vector<std::vector<std::string>> equations {
        {"a", "b"}, {"b", "c"}};
    
    const std::vector<double> values {2.0, 3.0};

    const std::vector<std::vector<std::string>> queries {
        {"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
    
    const std::vector<double> expected_output {6.0, 0.5, -1.0, 1.0, -1.0};

    EXPECT_EQ(expected_output, calcEquation(equations, values, queries));
}

TEST(CalcEquationTest, SampleTest2)
{
    const std::vector<std::vector<std::string>> equations {
        {"a", "b"}, {"b", "c"}, {"bc", "cd"}};
    
    const std::vector<double> values {1.5, 2.5, 5.0};

    const std::vector<std::vector<std::string>> queries {
        {"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}};
    
    const std::vector<double> expected_output {3.75, 0.4, 5.0, 0.2};

    EXPECT_EQ(expected_output, calcEquation(equations, values, queries));
}

TEST(CalcEquationTest, SampleTest3)
{
    const std::vector<std::vector<std::string>> equations {{"a", "b"}};
    
    const std::vector<double> values {0.5};

    const std::vector<std::vector<std::string>> queries {
        {"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}};
    
    const std::vector<double> expected_output {0.5, 2.0, -1.0, -1.0};

    EXPECT_EQ(expected_output, calcEquation(equations, values, queries));
}