#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

//! @brief Get min time for every node to receive signal from node k
//! @param[in] times Reference to vector of travel times [u, v, time_u_to_v]
//! @param[in] n     Number of nodes
//! @param[in] k     Node to send signal from
//! @return Min time for every node to receive signal from k or -1 if impossible
static int networkDelayTimeDS(const std::vector<std::vector<int>>& times,
                              int                                  n,
                              int                                  k)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /714/bonus/4841/
    //!          https://leetcode.com/problems/network-delay-time/description/
    //!
    //!          Time complexity depends on heap implementation but is generally
    //!          O((V + E) * log V) where V = number of vertices/nodes in graph
    //!          and E = number of edges. Heap operations cost up to O(log V).
    //!          There are O(V) pop operations and O(E) push operations.
    //!          Space complexity is O(V) for the heap and distances vector.

    std::vector<std::pair<int, int>> graph[n];

    for (const auto& edge : times)
    {
        //! Nodes are labeled 1-indexed so subtract 1 to make them 0-indexed
        const int u {edge[0] - 1};
        const int v {edge[1] - 1};
        const int w {edge[2]};

        graph[u].emplace_back(v, w);
    }

    std::vector<int> distances(n, std::numeric_limits<int>::max());

    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>> min_heap {};
    min_heap.emplace(0, k - 1);
    distances[k - 1] = 0;

    while (!min_heap.empty())
    {
        const auto [curr_dist, node] = min_heap.top();
        min_heap.pop();

        if (curr_dist > distances[node])
        {
            continue;
        }

        for (const auto& [neighbor, weight] : graph[node])
        {
            const int dist {curr_dist + weight};

            if (dist < distances[neighbor])
            {
                distances[neighbor] = dist;
                min_heap.emplace(dist, neighbor);
            }
        }
    }

    int min_time {std::numeric_limits<int>::min()};
    for (int node = 0; node < n; ++node)
    {
        min_time = std::max(min_time, distances[node]);
    }

    return min_time == std::numeric_limits<int>::max() ? -1 : min_time;

} // static int networkDelayTimeDS( ...

TEST(NetworkDelayTimeTest, SampleTest1)
{
    const std::vector<std::vector<int>> times {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};

    constexpr int n {4};
    constexpr int k {2};

    EXPECT_EQ(2, networkDelayTimeDS(times, n, k));
}

TEST(NetworkDelayTimeTest, SampleTest2)
{
    const std::vector<std::vector<int>> times {{1, 2, 1}};

    constexpr int n {2};
    constexpr int k {1};

    EXPECT_EQ(1, networkDelayTimeDS(times, n, k));
}

TEST(NetworkDelayTimeTest, SampleTest3)
{
    const std::vector<std::vector<int>> times {{1, 2, 1}};

    constexpr int n {2};
    constexpr int k {2};

    EXPECT_EQ(-1, networkDelayTimeDS(times, n, k));
}
