#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <vector>

//! @brief Get min cost to reach the top floor climbing one or two steps
//! @param[in] cost Vector of costs where cost[i] is the cost of ith step
//! @return Minimum cost to reach the top of the floor
static int minCostClimbingStairsTopDown(std::vector<int> cost)
{
    std::vector<int> memo(cost.size() + 1U, -1);

    //! Define dp(state) that returns the min cost to climb the stairs for a
    //! given state. i.e. dp(i) returns the min cost to climb the stairs up to
    //! the ith step (if the input was the subarray from index 0 up to and
    //! including i).
    std::function<int(int)> dp = [&](int i) {
        //! Base case: Can start at steps 0 or 1, dp(0) = dp(1) = 0
        if (i <= 1)
        {
            return 0;
        }

        //! Memoization improves time complexity from O(2 ^ n) to O(n) where
        //! n = cost.size()
        if (memo[i] != -1)
        {
            return memo[i];
        }

        //! Recurrence relation: To figure out min cost of climbing to 100th
        //! step, must have arrived from 99th or 98th step. Therefore, min cost
        //! of climbing to the 100th step is either min cost of getting to the
        //! 99th step + cost of 99th step or min cost of getting to the 98th
        //! step + cost of 98th step.
        //! dp(100) = min(dp(99) + cost(99), dp(98) + cost(98))
        memo[i] = std::min(dp(i - 1) + cost[i - 1], dp(i - 2) + cost[i - 2]);
        return memo[i];
    };

    return dp(static_cast<int>(cost.size()));

} // static int minCostClimbingStairsTopDown( ...

TEST(MinCostClimbingStairsTest, SampleTest1)
{
    const std::vector<int> cost {10, 15, 20};

    EXPECT_EQ(15, minCostClimbingStairsTopDown(cost));
}

TEST(MinCostClimbingStairsTest, SampleTest2)
{
    const std::vector<int> cost {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};

    EXPECT_EQ(6, minCostClimbingStairsTopDown(cost));
}
