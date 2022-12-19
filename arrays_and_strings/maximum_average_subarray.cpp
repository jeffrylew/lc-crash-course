#include <gtest/gtest.h>

#include <vector>

//! @brief First attempt solution to find max avg value of subarray size k
//! @param[in] nums Vector of integers
//! @param[in] k    Length of contiguous subarray
//! @return Max average value of subarray with length k
static double findMaxAverageFA(std::vector<int> nums, int k)
{
    double curr_sum {};
    for (int i = 0; i < k; ++i)
    {
        curr_sum += static_cast<double>(nums[i]);
    }

    auto max_sum = curr_sum;
    for (int i = k; i < static_cast<int>(nums.size()); ++i)
    {
        curr_sum += static_cast<double>(nums[i] - nums[i - k]);
        max_sum = std::max(max_sum, curr_sum);
    }

    return max_sum / static_cast<double>(k);

} // static double findMaxAverageFA( ...

TEST(FindMaxAverageTest, SampleTest)
{
    EXPECT_NEAR(12.75, findMaxAverageFA({1, 12, -5, -6, 50, 3}, 4), 0.01);
}