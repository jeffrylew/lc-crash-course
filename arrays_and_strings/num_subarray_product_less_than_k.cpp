#include <gtest/gtest.h>

#include <vector>

//! @brief Get number of continguous subarrays where product is less than k
//! @param[in] nums Vector of integers
//! @param[in] k    Maximum product in a subarray
//! @return Number of subarrays where product of all elements is less than k
static int numSubarrayProductLessThanK(std::vector<int> nums, int k)
{
    //! @details Time complexity is O(N) where N = nums.size(). Work done in
    //!          each loop iteration is constant.
    //!          Space complexity is O(1)
    //!
    //!          Number of subarrays ending at index is length of window after
    //!          reaching that index.

    if (k <= 1)
    {
        return 0;
    }
    
    int num_subarrays {};
    int curr_product {1};
    int left {};

    for (int right = 0; right < static_cast<int>(nums.size()); ++right)
    {
        curr_product *= nums[right];

        while (curr_product >= k)
        {
            curr_product /= nums[left++];
        }
        
        num_subarrays += right - left + 1;
    }

    return num_subarrays;

} // static int numSubarrayProductLessThanK( ...

TEST(NumSubarrayProductLessThanKTest, SampleTest)
{
    EXPECT_EQ(8, numSubarrayProductLessThanK({10, 5, 2, 6}, 100));
}