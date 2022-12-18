#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Find largest subarray sum for length k
//! @param[in] nums Vector of ints
//! @param[in] k    Length of subarray
//! @return largest sum of subarray with length k
static int findBestSubarray(std::vector<int> nums, int k)
{
    //! @details Time complexity O(N) where N = nums.size()
    //!          Space complexity O(1)
    
    int curr {};
    for (int i = 0; i < k; ++i)
    {
        curr += nums[i];
    }

    int largest_sum = curr;
    for (int i = k; i < static_cast<int>(nums.size()); ++i)
    {
        curr += nums[i] - nums[i - k];
        largest_sum = std::max(largest_sum, curr);
    }

    return largest_sum;

} // static int findBestSubarray( ...

TEST(FindBestSubarrayTest, SampleTest)
{
    EXPECT_EQ(18, findBestSubarray({3, -1, 4, 12, -8, 5, 6}, 4));
}