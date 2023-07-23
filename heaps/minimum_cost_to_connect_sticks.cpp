#include <gtest/gtest.h>

#include <functional>
#include <queue>
#include <vector>

//! @brief First attempt to get min cost of connecting all sticks into one
//! @param[in] sticks Vector of positive integer lengths
//! @return Minimum cost of connecting all sticks into one stick
static int connectSticksFA(std::vector<int> sticks)
{
    std::priority_queue minHeap(
        sticks.cbegin(), sticks.cend(), std::greater<int>());

    int cost {};

    while (minHeap.size() > 1ULL)
    {
        const int smallStick1 {minHeap.top()};
        minHeap.pop();

        const int smallStick2 {minHeap.top()};
        minHeap.pop();

        cost += smallStick1 + smallStick2;
        minHeap.push(smallStick1 + smallStick2);
    }

    return cost;
}

TEST(ConnectSticksTest, SampleTest)
{
    EXPECT_EQ(14, connectSticksFA({2, 4, 3}));

    EXPECT_EQ(30, connectSticksFA({1, 8, 3, 5}));

    EXPECT_EQ(0, connectSticksFA({5}));
}