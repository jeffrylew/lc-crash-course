#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Find length of longest subarray with sum <= k
//! @param[in] nums Vector of positive integers
//! @param[in] k    Max sum of sliding window
//! @return Length of longest subarray with sum less than or equal to k
static int findLength(std::vector<int> nums, int k)
{
    //! @details Time complexity O(N) where N = nums.size(). Work done in inner
    //!          while loop is amortized O(1). It can only iterate N times in
    //!          total for the entire algorithm - so even if it runs N times on
    //!          one iteration of the for loop, it cannot run for all other
    //!          N - 1 iterations, averaging to O(1).
    //!          Space complexity is O(1) since only using 3 integer variables

    int left {};
    int curr {}; // Tracks sum of current window/subarray
    int max_subarray_size {};

    for (int right = 0; right < static_cast<int>(nums.size()); ++right)
    {
        curr += nums[right];

        while (curr > k)
        {
            curr -= nums[left++];
        }
        max_subarray_size = std::max(max_subarray_size, right - left + 1);
    }

    return max_subarray_size;

} // static int findLength( ...

TEST(FindLengthTest, SampleTest)
{
    EXPECT_EQ(4, findLength({3, 1, 2, 7, 4, 2, 1, 1, 5}, 8));
}