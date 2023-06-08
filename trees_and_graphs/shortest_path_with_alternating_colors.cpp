#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

struct State
{
    int node {};
    int color {};
    int steps {};

    State(int node_in, int color_in, int steps_in)
        : node {node_in}
        , color {color_in}
        , steps {steps_in}
    {
    }
};

std::vector<int> shortestAlternatingPaths(
    int                                  n,
    const std::vector<std::vector<int>>& redEdges,
    const std::vector<std::vector<int>>& blueEdges)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /707/traversals-trees-graphs/4631/
    //!
    //!          Time complexity O(N + E) where N = number of nodes and
    //!          E = total number of edges (both colors). The number of states
    //!          is the product of the ranges of each state variable. Here, the
    //!          range of color is always 2 so it doesn't affect the complexity.
    //!          Space complexity O(N + E) due to graph, seen, and queue

    constexpr int RED {};
    constexpr int BLUE {1};

    //! Map <<color, node>, <vector of neighbors accessed through edge color>>
    std::map<std::pair<int, int>, std::vector<int>> graph {};
    for (const auto [nodeA, nodeB] : redEdges)
    {
        graph[{RED, nodeA}].push_back(nodeB);
    }

    for (const auto [nodeA, nodeB] : blueEdges)
    {
        graph[{BLUE, nodeA}].push_back(nodeB);
    }

    std::vector<int>               ans(n, std::numeric_limits<int>::max());
    std::queue<State>              queue {};
    std::vector<std::vector<bool>> seen(n, std::vector<bool>(2, false));

    //! Add initial node 0 to queue and seen
    queue.emplace(0, RED, 0);  // node, color, steps
    queue.emplace(0, BLUE, 0); // node, color, steps
    seen[0][RED]  = true; // node, color
    seen[0][BLUE] = true; // node, color

    while (not queue.empty())
    {
        const auto curr_state = queue.front();
        queue.pop();

        const int node {curr_state.node};
        const int color {curr_state.color};
        const int steps {curr_state.steps};

        ans[node] = std::min(ans[node], steps);

        for (const int neighbor : graph[{color, node}])
        {
            if (not seen[neighbor][1 - color])
            {
                seen[neighbor][1 - color] = true;
                queue.emplace(neighbor, 1 - color, steps + 1);
            }
        }
    }

    std::replace(ans.begin(), ans.end(), std::numeric_limits<int>::max(), -1);

    return ans;

} // std::vector<int> shortestAlternatingPaths( ...

TEST(ShortestAlternatingPathsTest, SampleTest1)
{
    const std::vector<std::vector<int>> redEdges {{0, 1}, {1, 2}};
    const std::vector<std::vector<int>> blueEdges {};
    const std::vector<int>              expected {0, 1, -1};

    EXPECT_EQ(expected, shortestAlternatingPaths(3, redEdges, blueEdges));
}

TEST(ShortestAlternatingPathsTest, SampleTest2)
{
    const std::vector<std::vector<int>> redEdges {{0, 1}};
    const std::vector<std::vector<int>> blueEdges {{2, 1}};
    const std::vector<int>              expected {0, 1, -1};

    EXPECT_EQ(expected, shortestAlternatingPaths(3, redEdges, blueEdges));
}
