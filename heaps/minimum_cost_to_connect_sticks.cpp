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

//! @brief Discussion solution to get min cost of connecting all sticks into one
//! @param[in] sticks Vector of positive integer lengths
//! @return Minimum cost of connecting all sticks into one stick
static int connectSticksDS(std::vector<int> sticks)
{
    //! @details https://leetcode.com/problems/minimum-cost-to-connect-sticks/
    //!          editorial/
    //!
    //!          Time complexity O(N * log N) where N = sticks.size(). Adding
    //!          N elements to priority queue requires O(N * log N). Removing
    //!          two of smallest elements and adding one element to the priority
    //!          queue will take N - 1 operations. Both add and remove take
    //!          O(log N) so the time complexity is O(N * log N).
    //!          Space complexity O(N) to store N elements in priority queue.

    int totalCost {};

    //! Add all sticks to the min heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap(
        sticks.cbegin(), sticks.cend());

    //! Combine two of smallest sticks until we are left with one
    while (minHeap.size() > 1ULL)
    {
        const int stick1 {minHeap.top()};
        minHeap.pop();

        const int stick2 {minHeap.top()};
        minHeap.pop();

        const int cost {stick1 + stick2};
        totalCost += cost;
        minHeap.push(cost);
    }

    return totalCost;
}

TEST(ConnectSticksTest, SampleTest)
{
    EXPECT_EQ(14, connectSticksFA({2, 4, 3}));
    EXPECT_EQ(14, connectSticksDS({2, 4, 3}));

    EXPECT_EQ(30, connectSticksFA({1, 8, 3, 5}));
    EXPECT_EQ(30, connectSticksDS({1, 8, 3, 5}));

    EXPECT_EQ(0, connectSticksFA({5}));
    EXPECT_EQ(0, connectSticksDS({5}));
}