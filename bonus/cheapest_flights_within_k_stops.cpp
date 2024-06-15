#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <tuple>
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

//! @brief Bellman Ford discussion solution
//! @param[in] n       Number of cities
//! @param[in] flights Reference to vector, flights[i] = [from_i, to_i, price_i]
//! @param[in] src     Source city
//! @param[in] dst     Destination city
//! @param[in] k       Max number of stops from src to dst
//! @return Cheapest price from src to dst with k stops max, else -1 if no route
static int findCheapestPriceDS2(int                                  n,
                                const std::vector<std::vector<int>>& flights,
                                int                                  src,
                                int                                  dst,
                                int                                  k)
{
    //! @details https://leetcode.com/problems/cheapest-flights-within-k-stops
    //!
    //!          Time complexity O((n + E) * k) where n = number of cities and
    //!          E = number of flights. Iterating over all flights (k + 1) times
    //!          takes O(E * k). At the start and end of each iteration, also
    //!          swap costs vectors, which takes O(n * k) for all iterations.
    //!          This gives O(E * k + n * k) = O((n + E) * k)
    //!          Space complexity O(n) for costs and temp vectors which use O(n)

    //! Costs from source to all other cities
    std::vector<int> costs(n, std::numeric_limits<int>::max());
    costs[src] = 0;

    //! Run only k + 1 times since want minimum cost in k flights
    for (int num_flights = 0; num_flights <= k; ++num_flights)
    {
        //! Create copy of costs vector
        auto temp = costs;

        for (const auto& flight : flights)
        {
            if (costs[flight[0]] != std::numeric_limits<int>::max())
            {
                temp[flight[1]] = std::min(temp[flight[1]],
                                           costs[flight[0]] + flight[2]);
            }
        }

        //! Copy/move temp vector into costs
        costs = std::move(temp);
    }

    return costs[dst] == std::numeric_limits<int>::max() ? -1 : costs[dst];

} // static int findCheapestPriceDS2( ...

//! @brief Dijkstra discussion solution
//! @param[in] n       Number of cities
//! @param[in] flights Reference to vector, flights[i] = [from_i, to_i, price_i]
//! @param[in] src     Source city
//! @param[in] dst     Destination city
//! @param[in] k       Max number of stops from src to dst
//! @return Cheapest price from src to dst with k stops max, else -1 if no route
static int findCheapestPriceDS3(int                                  n,
                                const std::vector<std::vector<int>>& flights,
                                int                                  src,
                                int                                  dst,
                                int                                  k)
{
    //! @details https://leetcode.com/problems/cheapest-flights-within-k-stops
    //!
    //!          Time complexity O(n + E * k * log(E * k)) where E = number of
    //!          flights and n = number of cities.  Assume city A is popped out
    //!          of the min_heap during an iteration. If nflights_from_src taken
    //!          to visit A are more than num_flights[A] then do not iterate
    //!          over A's neighbors. Otherwise, nflights_from_src can be less
    //!          than num_flights[A] a total of k times. A can be popped the
    //!          first time with k flights, followed by k - 1 flights, etc.
    //!          until 1 flight. The same argument is valid for any other city.
    //!          Thus, each flight can only be processed k times, resulting in
    //!          O(E * k) elements processed. It takes O(E * k * log(E * k)) for
    //!          the min_heap to push or pop E * k elements. Add O(n) time for
    //!          using the num_flights vector (construction is linear to n, (3)
    //!          from https://en.cppreference.com/w/cpp/container/vector/vector)
    //!          Space complexity O(n + E * k). adj vector requires O(E) space.
    //!          num_flights vector requires O(n). The min_heap can only have
    //!          O(E * k) elements.

    //! Adjacency list adj[X] contains neighboring cities of X and price to move
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (const auto& flight : flights)
    {
        adj[flight[0]].emplace_back(flight[1], flight[2]);
    }

    //! Stores minimum number of flights to reach a city from src. Initialize
    //! with large values to indicate we haven't reached any cities yet
    std::vector<int> num_flights(n, std::numeric_limits<int>::max());

    //! Stores <cost from src city, current city, number of flights from src>
    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>,
                        std::greater<std::tuple<int, int, int>>> min_heap {};
    min_heap.emplace(0, src, 0);

    while (!min_heap.empty())
    {
        const auto [cost_from_src, city, nflights_from_src] = min_heap.top();
        min_heap.pop();

        //! Already encountered a path with a lower cost and fewer flights
        //! or the number of flights exceeds the limit
        if (nflights_from_src > num_flights[city] || nflights_from_src > k + 1)
        {
            continue;
        }

        num_flights[city] = nflights_from_src;

        if (city == dst)
        {
            return cost_from_src;
        }

        for (const auto& [neighbor, price] : adj[city])
        {
            min_heap.emplace(
                cost_from_src + price, neighbor, nflights_from_src + 1);
        }
    }

    return -1;

} // static int findCheapestPriceDS3( ...

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
    EXPECT_EQ(700, findCheapestPriceDS2(n, flights, src, dst, k));
    EXPECT_EQ(700, findCheapestPriceDS3(n, flights, src, dst, k));
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
    EXPECT_EQ(200, findCheapestPriceDS2(n, flights, src, dst, k));
    EXPECT_EQ(200, findCheapestPriceDS3(n, flights, src, dst, k));
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
    EXPECT_EQ(500, findCheapestPriceDS2(n, flights, src, dst, k));
    EXPECT_EQ(500, findCheapestPriceDS3(n, flights, src, dst, k));
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
    EXPECT_EQ(7, findCheapestPriceDS2(n, flights, src, dst, k));
    EXPECT_EQ(7, findCheapestPriceDS3(n, flights, src, dst, k));
}
