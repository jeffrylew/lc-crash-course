#include <gtest/gtest.h>

#include <cmath>
#include <queue>
#include <vector>

//! @brief First attempt to get min number of stones after applying k operations
//! @param[in] piles Vector where piles[i] = number of stones in ith pile
//! @param[in] k     Number of floor(piles[i] / 2) removal operations to perform
//! @return Min total number of stones remaining after applying k operations
static int minStoneSumFA(std::vector<int> piles, int k)
{
    std::priority_queue<int> heap(piles.cbegin(), piles.cend());

    while (k-- > 0)
    {
        const auto largestPile = heap.top();
        heap.pop();

        //! std::floor overloads provided for integer types
        //! https://en.cppreference.com/w/cpp/numeric/math/floor
        const auto toRemove = static_cast<int>(std::floor(largestPile / 2.0));

        heap.push(largestPile - toRemove);
    }

    int total {};
    while (not heap.empty())
    {
        total += heap.top();
        heap.pop();
    }

    return total;
}

TEST(MinStoneSumTest, SampleTest)
{
    EXPECT_EQ(12, minStoneSumFA({5, 4, 9}, 2));

    EXPECT_EQ(12, minStoneSumFA({4, 3, 6, 7}, 3));
}