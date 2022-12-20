#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Minimum value to get positive step by step sum
//! @param[in] nums Vector of integers
//! @return Minimum positive value of startValue such that step by step sum >= 1
static int minStartValueFA(std::vector<int> nums)
{
    int min_start_value {};
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

TEST(MinStartValueTest, SampleTest)
{
    EXPECT_EQ(5, minStartValueFA({-3, 2, -3, 4, 2}));
    EXPECT_NE(1, minStartValueFA({1, 2}));
}