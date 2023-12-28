#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <vector>

//! @brief Get max money can rob without triggering alarm from 2 adjacent homes
//! @param[in] nums Vector of money in homes, ith house has nums[i] money
//! @return Most money can rob without alerting police
static int robTopDown(std::vector<int> nums)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /712/dynamic-programming/4541/
    //!
    //!          Time complexity O(n) where n = nums.size() because only visit
    //!          each state once. At each state, applying recurrence relation is
    //!          O(1).
    //!          Space complexity O(n) to cache results for each state.

    const auto nums_size = static_cast<int>(nums.size());

    if (nums_size == 1)
    {
        //! Prevent out of bounds error
        return nums[0];
    }

    std::vector<int> memo(nums.size(), -1);

    std::function<int(int)> dp = [&](int i) -> int {
        if (i == 0)
        {
            //! If there is only one house, rob it
            return nums[0];
        }

        if (i == 1)
        {
            //! If there are two houses, rob the one with more money
            return std::max(nums[0], nums[1]);
        }

        if (memo[i] != -1)
        {
            return memo[i];
        }

        //! Recurrence relation
        //! Option 1: We rob house i and gain nums[i] money. Cannot rob previous
        //!           house so amount of money from 2 houses ago is dp(i - 2).
        //! Option 2: We don't rob house. Could have arrived from previous house
        //!           so we have dp(i - 1) money.
        return memo[i] = std::max(dp(i - 1), dp(i - 2) + nums[i]);
    };

    return dp(nums_size - 1);

} // static int robTopDown( ...

//! @brief Get max money can rob without triggering alarm from 2 adjacent homes
//! @param[in] nums Vector of money in homes, ith house has nums[i] money
//! @return Most money can rob without alerting police
static int robBottomUp(std::vector<int> nums)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /712/dynamic-programming/4541/

    const auto nums_size = static_cast<int>(nums.size());

    if (nums_size == 1)
    {
        //! Avoid out-of-bounds error when setting base case
        return nums[0];
    }

    std::vector<int> dp(nums.size());

    //! Base cases
    dp[0] = nums[0];
    dp[1] = std::max(nums[0], nums[1]);

    for (int i = 2; i < nums_size; ++i)
    {
        //! Recurrence relation
        dp[i] = std::max(dp[i - 1], dp[i - 2] + nums[i]);
    }

    return dp[nums_size - 1];

} // static int robBottomUp( ...

TEST(RobTest, SampleTest1)
{
    const std::vector<int> nums {1, 2, 3, 1};

    EXPECT_EQ(4, robTopDown(nums));
    EXPECT_EQ(4, robBottomUp(nums));
}

TEST(RobTest, SampleTest2)
{
    const std::vector<int> nums {2, 7, 9, 3, 1};

    EXPECT_EQ(12, robTopDown(nums));
    EXPECT_EQ(12, robBottomUp(nums));
}
