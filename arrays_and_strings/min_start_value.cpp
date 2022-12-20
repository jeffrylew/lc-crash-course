#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Minimum value to get positive step by step sum
//! @param[in] nums Vector of integers
//! @return Minimum positive value of startValue such that step by step sum >= 1
static int minStartValueFA(std::vector<int> nums)
{
    int min_start_value {1};
    if (nums[0] < 1)
    {
        min_start_value = 1 - nums[0];
    }

    for (int i = 1; i < static_cast<int>(nums.size()); ++i)
    {
        nums[i] += nums[i - 1];
        if (nums[i] < 1)
        {
            min_start_value = std::max(min_start_value, 1 - nums[i]);
        }
    }

    return min_start_value;

} // static int minStartValueFA( ...

static int minStartValueDS(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/
    //!          minimum-value-to-get-positive-step-by-step-sum/solutions/
    //!          1513266/official-solution/
    //!
    //!          Time complexity O(n)
    //!          Space complexity O(1)

    //! Use total for current step-by-step total, minVal for minimum
    //! step-by-step total among all sums
    int minVal {};
    int total {};

    //! Iterate over array and get minimum step-by-step total
    for (int num : nums)
    {
        total += num;
        minVal = std::min(minVal, total);
    }

    //! Minimum step-by-step total must equal 1 so increase startValue from 0 to
    //! -minVal + 1
    return 1 - minVal;

} // static int minStartValueDS( ...

TEST(MinStartValueTest, SampleTest)
{
    EXPECT_EQ(5, minStartValueFA({-3, 2, -3, 4, 2}));
    EXPECT_EQ(1, minStartValueFA({1, 2}));
    EXPECT_EQ(5, minStartValueFA({1, -2, -3}));

    EXPECT_EQ(5, minStartValueDS({-3, 2, -3, 4, 2}));
    EXPECT_EQ(1, minStartValueDS({1, 2}));
    EXPECT_EQ(5, minStartValueDS({1, -2, -3}));
}