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

static int findBestSubarrayDS2(std::vector<int> nums, int k)
{
    int curr {};
    int largest_sum {};

    for (int i = 0; i < static_cast<int>(nums.size()); ++i)
    {
        if (i >= k)
        {
            largest_sum = std::max(largest_sum, curr);
            curr -= nums[i - k];
        }
        curr += nums[i];
    }

    return std::max(largest_sum, curr);

} // static int findBestSubarrayDS2( ...

TEST(FindBestSubarrayTest, SampleTest)
{
    EXPECT_EQ(18, findBestSubarray({3, -1, 4, 12, -8, 5, 6}, 4));
    EXPECT_EQ(18, findBestSubarrayDS2({3, -1, 4, 12, -8, 5, 6}, 4));
}