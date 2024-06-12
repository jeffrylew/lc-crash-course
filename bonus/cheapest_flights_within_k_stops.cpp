#include <gtest/gtest.h>

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

    //! @todo

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
