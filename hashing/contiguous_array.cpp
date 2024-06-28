#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Get max length of a contiguous subarray with an equal number of 0, 1
//! @param[in] nums Vector of binary integers 0 and 1
//! @return Max length of a contiguous subarray with an equal number of 0 and 1
static int findMaxLengthFA(std::vector<int> nums)
{
    //! @details First attempt solution does not pass SampleTest3

    const auto       nums_size = static_cast<int>(nums.size());
    std::vector<int> prefix(nums.size() + 1U);
    for (int idx = 0; idx < nums_size; ++idx)
    {
        prefix[idx + 1] = prefix[idx] + nums[idx];
    }

    int max_len {};
    int right_bound {};
    for (int left_bound = 0; left_bound < nums_size; ++left_bound)
    {
        int window_sum {prefix[left_bound + 1] - prefix[right_bound]};
        int window_size {left_bound - right_bound + 1};

        if (window_sum * 2 == window_size)
        {
            max_len = std::max(max_len, window_size);
            continue;
        }

        while (window_sum * 2 > window_size)
        {
            window_sum  = prefix[left_bound + 1] - prefix[++right_bound];
            window_size = left_bound - right_bound + 1;

            if (window_sum * 2 == window_size)
            {
                max_len = std::max(max_len, window_size);
                break;
            }
        }
    }

    return max_len;

} // static int findMaxLengthFA( ...

//! @brief Brute force discussion solution
//! @param[in] nums Vector of binary integers 0 and 1
//! @return Max length of a contiguous subarray with an equal number of 0 and 1
static int findMaxLengthDS1(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/contiguous-array/editorial/
    //!
    //!          Time complexity O(N ^ 2) where N = nums.size(). Consider every
    //!          possible subarray by traversing over the complete vector for
    //!          every possible starting point.
    //!          Space complexity O(1) for zeros and ones.

    int max_len {};

    const auto nums_size = static_cast<int>(nums.size());

    for (int start = 0; start < nums_size; ++start)
    {
        int zeros {};
        int ones {};

        for (int end = start; end < nums_size; ++end)
        {
            if (nums[end] == 0)
            {
                ++zeros;
            }
            else
            {
                ++ones;
            }

            if (zeros == ones)
            {
                max_len = std::max(max_len, end - start + 1);
            }
        }
    }

    return max_len;

} // static int findMaxLengthDS1( ...

TEST(FindMaxLengthTest, SampleTest1)
{
    EXPECT_EQ(2, findMaxLengthFA({0, 1}));
    EXPECT_EQ(2, findMaxLengthDS1({0, 1}));
}

TEST(FindMaxLengthTest, SampleTest2)
{
    EXPECT_EQ(2, findMaxLengthFA({0, 1, 0}));
    EXPECT_EQ(2, findMaxLengthDS1({0, 1, 0}));
}

TEST(FindMaxLengthTest, SampleTest3)
{
    const std::vector<int> nums {0, 0, 1, 0, 0, 0, 1, 1};

    EXPECT_EQ(0, findMaxLengthFA(nums));
    EXPECT_NE(6, findMaxLengthFA(nums));
    EXPECT_EQ(6, findMaxLengthDS1(nums));
}
