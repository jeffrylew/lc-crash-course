#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <vector>

//! @brief Get length of longest strictly increasing subsequence
//! @param[in] nums Vector of ints
//! @return Length of longest strictly increasing subsequence
static int lengthOfLISTopDown(const std::vector<int>& nums)
{
    //! @details https://leetcode.com/problems/longest-increasing-subsequence/
    //!
    //!          Time complexity O(n ^ 2) where n = nums.size() due to nested
    //!          loop. This is because the work done at each state is linear
    //!          with n and there are n states.
    //!          Space complexity O(n) is the number of states.

    std::vector<int> memo(nums.size(), -1);

    std::function<int(int)> dp = [&](int i) {
        if (memo[i] != -1)
        {
            return memo[i];
        }

        //! Base case
        int len {1};
        for (int j = 0; j < i; ++j)
        {
            if (nums[i] > nums[j])
            {
                len = std::max(len, dp(j) + 1);
            }
        }

        return memo[i] = len;
    };

    int ans {};
    for (int i = 0; i < static_cast<int>(nums.size()); ++i)
    {
        ans = std::max(ans, dp(i));
    }

    return ans;

} // static int lengthOfLISTopDown( ...

//! @brief Get length of longest strictly increasing subsequence
//! @param[in] nums Vector of ints
//! @return Length of longest strictly increasing subsequence
static int lengthOfLISBottomUp(const std::vector<int>& nums)
{
    int ans {1};

    std::vector<int> dp(nums.size(), 1);

    for (int i = 0; i < static_cast<int>(nums.size()); ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (nums[i] > nums[j])
            {
                dp[i] = std::max(dp[i], dp[j] + 1);
                ans = std::max(ans, dp[i]);
            }
        }
    }

    return ans;
}

TEST(LengthOfLISTest, SampleTest1)
{
    const std::vector<int> nums {10, 9, 2, 5, 3, 7, 101, 18};

    EXPECT_EQ(4, lengthOfLISTopDown(nums));
    EXPECT_EQ(4, lengthOfLISBottomUp(nums));
}

TEST(LengthOfLISTest, SampleTest2)
{
    const std::vector<int> nums {0, 1, 0, 3, 2, 3};

    EXPECT_EQ(4, lengthOfLISTopDown(nums));
    EXPECT_EQ(4, lengthOfLISBottomUp(nums));
}

TEST(LengthOfLISTest, SampleTest3)
{
    const std::vector<int> nums {7, 7, 7, 7, 7, 7, 7};

    EXPECT_EQ(1, lengthOfLISTopDown(nums));
    EXPECT_EQ(1, lengthOfLISBottomUp(nums));
}
