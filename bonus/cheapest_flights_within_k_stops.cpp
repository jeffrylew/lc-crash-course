#include <gtest/gtest.h>

#include <functional>
#include <limits>
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

//! @brief Breadth First Search discussion solution
//! @param[in] n       Number of cities
//! @param[in] flights Reference to vector, flights[i] = [from_i, to_i, price_i]
//! @param[in] src     Source city
//! @param[in] dst     Destination city
//! @param[in] k       Max number of stops from src to dst
//! @return Cheapest price from src to dst with k stops max, else -1 if no route
static int findCheapestPriceDS1(int                                  n,
                                const std::vector<std::vector<int>>& flights,
                                int                                  src,
                                int                                  dst,
                                int                                  k)
{
    //! @details https://leetcode.com/problems/cheapest-flights-within-k-stops
    //!
    //!          Time complexity O(n + E * k) where n = number of cities, k is
    //!          the max number of stops, and E = number of flights. Depending
    //!          on improvements in the minimum cost for each city, may process
    //!          each flight/edge multiple times. However, the max number of
    //!          times a flight/edge can be processed is limited by k since that
    //!          is the number of levels investigated. In the worst case, this
    //!          takes O(E * k) time. We also need O(E) to initialize the
    //!          adjacency vector and O(n) to initialize the costs vector.
    //!          Space complexity O(n + E * k). We are processing at most E * k
    //!          edges so the queue uses O(E * k) in the worst case. Also need
    //!          O(E) for the adjacency vector and O(n) for the costs vector.

    //! Adjacency list contains all neighbors of city and
    //! corresponding price it takes to move to a neighbor
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (const auto& flight : flights)
    {
        adj[flight[0]].emplace_back(flight[1], flight[2]);
    }

    //! costs stores min price to reach city from src
    std::vector<int> costs(n, std::numeric_limits<int>::max());

    //! city_cost stores <city, cost> pairs
    std::queue<std::pair<int, int>> city_cost {};
    city_cost.emplace(src, 0);

    int stops {};
    while (stops <= k && !city_cost.empty())
    {
        auto level_size = static_cast<int>(city_cost.size());

        //! Iterate on current level
        while (level_size-- > 0)
        {
            const auto [curr_city, cost_to_curr_city] = city_cost.front();
            city_cost.pop();

            //! Iterate over neighbors of popped city
            for (const auto& [neighbor, price] : adj[curr_city])
            {
                if (cost_to_curr_city + price >= costs[neighbor])
                {
                    continue;
                }

                costs[neighbor] = cost_to_curr_city + price;
                city_cost.emplace(neighbor, costs[neighbor]);
            }
        }
        ++stops;
    }

    return costs[dst] == std::numeric_limits<int>::max() ? -1 : costs[dst];

} // static int findCheapestPriceDS1( ...

TEST(FindCheapestPriceTest, SampleTest1)
{
    const std::vector<std::vector<int>> flights {
        {0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}};

    constexpr int n {4};
    constexpr int src {0};
    constexpr int dst {3};
    constexpr int k {1};

    EXPECT_EQ(700, findCheapestPriceFA(n, flights, src, dst, k));
    EXPECT_EQ(700, findCheapestPriceDS1(n, flights, src, dst, k));
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
    EXPECT_EQ(200, findCheapestPriceDS1(n, flights, src, dst, k));
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
    EXPECT_EQ(500, findCheapestPriceDS1(n, flights, src, dst, k));
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
    EXPECT_EQ(7, findCheapestPriceDS1(n, flights, src, dst, k));
}
