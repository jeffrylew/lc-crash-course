#include <gtest/gtest.h>

#include <functional>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

//! @brief First attempt to get cheapest price from src to dst with k stops max
//! @param[in] n       Number of cities
//! @param[in] flights Reference to vector, flights[i] = [from_i, to_i, price_i]
//! @param[in] src     Source city
//! @param[in] dst     Destination city
//! @param[in] k       Max number of stops from src to dst
//! @return Cheapest price from src to dst with k stops max, else -1 if no route
static int findCheapestPriceFA(int                                  n,
                               const std::vector<std::vector<int>>& flights,
                               int                                  src,
                               int                                  dst,
                               int                                  k)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /714/bonus/4842/
    //!
    //!          First attempt solution does not pass SampleTest4 below

    std::unordered_map<int, std::vector<std::pair<int, int>>> graph {};
    for (const auto& flight : flights)
    {
        // <from, <to, price>>
        graph[flight[0]].emplace_back(flight[1], flight[2]);
    }

    //! Initial cost should be greater than price_max * n = 1E4 * 100
    constexpr int init_cost {10000000};

    //! <cost to get to city, number of stops>
    //! Initialize with -1 since direct flight between two cities has 0 stops
    std::vector<std::pair<int, int>> cost_stops(n, {init_cost, -1});
    cost_stops[src] = {0, -1};

    //! Min heap of <cost to get from src to city, city>
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>> min_heap {};
    min_heap.emplace(0, src);

    while (!min_heap.empty())
    {
        const auto [cost_to_curr_city, curr_city] = min_heap.top();
        min_heap.pop();

        //! Investigate neighboring cities that can be reached from curr_city
        for (const auto& [neighbor_city, price] : graph[curr_city])
        {
            //! It will take more than k stops to reach neighbor_city so skip it
            const int stops_to_neighbor {cost_stops[curr_city].second + 1};
            if (stops_to_neighbor > k)
            {
                continue;
            }

            const int cost_to_neighbor {cost_to_curr_city + price};
            if (cost_to_neighbor < cost_stops[neighbor_city].first
                && (neighbor_city == dst || stops_to_neighbor < k))
            {
                cost_stops[neighbor_city] =
                    {cost_to_neighbor, stops_to_neighbor};

                min_heap.emplace(cost_to_neighbor, neighbor_city);
            }
        }
    }

    return cost_stops[dst].first == init_cost ? -1 : cost_stops[dst].first;

} // static int findCheapestPriceFA( ...

TEST(FindCheapestPriceTest, SampleTest1)
{
    const std::vector<std::vector<int>> flights {
        {0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}};

    constexpr int n {4};
    constexpr int src {0};
    constexpr int dst {3};
    constexpr int k {1};

    EXPECT_EQ(700, findCheapestPriceFA(n, flights, src, dst, k));
}

TEST(FindCheapestPriceTest, SampleTest2)
{
    const std::vector<std::vector<int>> flights {
        {0, 1, 100}, {1, 2, 100}, {0, 2, 500}};

    constexpr int n {3};
    constexpr int src {0};
    constexpr int dst {2};
    constexpr int k {1};

    EXPECT_EQ(200, findCheapestPriceFA(n, flights, src, dst, k));
}

TEST(FindCheapestPriceTest, SampleTest3)
{
    const std::vector<std::vector<int>> flights {
        {0, 1, 100}, {1, 2, 100}, {0, 2, 500}};

    constexpr int n {3};
    constexpr int src {0};
    constexpr int dst {2};
    constexpr int k {0};

    EXPECT_EQ(500, findCheapestPriceFA(n, flights, src, dst, k));
}

TEST(FindCheapestPriceTest, SampleTest4)
{
    const std::vector<std::vector<int>> flights {
        {0, 1, 5}, {1, 2, 5}, {0, 3, 2}, {3, 1, 2}, {1, 4, 1}, {4, 2, 1}};

    constexpr int n {5};
    constexpr int src {0};
    constexpr int dst {2};
    constexpr int k {2};

    EXPECT_NE(7, findCheapestPriceFA(n, flights, src, dst, k));
    EXPECT_EQ(9, findCheapestPriceFA(n, flights, src, dst, k));
}
