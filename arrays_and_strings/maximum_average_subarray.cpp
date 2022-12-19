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

//! @brief First discussion solution using prefix sums
//! @param[in] nums Vector of integers
//! @param[in] k    Length of contiguous subarray
//! @return Max average value of subarray with length k
static double findMaxAverageDS1(std::vector<int> nums, int k)
{
    //! @details https://leetcode.com/problems/maximum-average-subarray-i/
    //!          solutions/127562/official-solution/
    //!
    //!          Time complexity O(N) where N = nums_size. Iterate over nums
    //!          once to populate sum vector. Then iterate over n - k elements
    //!          of sum to determine max average.
    //!          Space complexity O(N) for sum vector of size N

    std::vector<int> sum(nums.size());
    sum[0] = nums[0];

    const auto nums_size = static_cast<int>(nums.size());
    for (int i = 1; i < nums_size; ++i)
    {
        sum[i] = sum[i - 1] + nums[i];
    }

    double max_avg = sum[k - 1] * 1.0 / k;
    for (int i = k; i < nums_size; ++i)
    {
        max_avg = std::max(max_avg, (sum[i] - sum[i - k]) * 1.0 / k);
    }

    return max_avg;

} // static double findMaxAverageDS1( ...

TEST(FindMaxAverageTest, SampleTest)
{
    EXPECT_NEAR(12.75, findMaxAverageFA({1, 12, -5, -6, 50, 3}, 4), 0.01);
    EXPECT_NEAR(12.75, findMaxAverageDS1({1, 12, -5, -6, 50, 3}, 4), 0.01);
}