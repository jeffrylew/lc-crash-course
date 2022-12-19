#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Maximum number of consecutive 1s if can flip at most k 0s
//! @param[in] nums Vector of binary integers
//! @param[in] k    Max number of 0s that can be flipped
//! @return Max number of consecutive 1s in vector if can flip at most k 0s
static int longestOnesFA(std::vector<int> nums, int k)
{
    int curr_zeros {};
    int max_ones {};
    int left {};

    for (int right = 0; right < static_cast<int>(nums.size()); ++right)
    {
        if (nums[right] == 0)
        {
            ++curr_zeros;
        }
        
        while (curr_zeros > k)
        {
            if (nums[left++] == 0)
            {
                --curr_zeros;
            }
        }
        
        max_ones = std::max(max_ones, right - left + 1);
    }

    return max_ones;

} // static int longestOnesFA( ...

TEST(LongestOnesTest, SampleTest)
{
    EXPECT_EQ(6, longestOnesFA({1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0}, 2));
}