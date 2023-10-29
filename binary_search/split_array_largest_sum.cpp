#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <numeric>
#include <vector>

//! @brief Split nums into k non-empty subarrays so largest sum is minimized
//! @param[in] nums Vector of ints
//! @param[in] k    Number of non-empty subarrays to split
//! @return Minimized largest sum of the split
static int splitArrayFA(std::vector<int> nums, int k)
{
    //! @details

    const int total_sum {std::accumulate(nums.cbegin(), nums.cend(), 0)};
    int       left {*std::min_element(nums.cbegin(), nums.cend())};
    int       right {total_sum};
    int       min_largest_sum {total_sum};

    while (left <= right)
    {
        //! min_subarray_sum is the minimum subarray sum for k subarrays
        //! If all subarrays have a sum larger than this minimum then
        //! track the largest subarray sum
        const int min_subarray_sum {left + (right - left) / 2};
        int       num_subarrays {};
        int       current_subarray_sum {};
        int       largest_subarray_sum {};
    
        for (const int num : nums)
        {
            current_subarray_sum += num;

            if (current_subarray_sum >= min_subarray_sum)
            {
                ++num_subarrays;
                largest_subarray_sum =
                  std::max(largest_subarray_sum, current_subarray_sum);
                current_subarray_sum = 0;
            }
        }

        if (num_subarrays >= k)
        {
            min_largest_sum = std::min(min_largest_sum, largest_subarray_sum);
            left            = min_subarray_sum + 1;
        }
        else
        {
            right = min_subarray_sum - 1;
        }
    }

    return min_largest_sum;
}

TEST(SplitArrayTest, SampleTest)
{
    EXPECT_EQ(18, splitArrayFA({7, 2, 5, 10, 8}, 2));

    EXPECT_EQ(9, splitArrayFA({1, 2, 3, 4, 5}, 2));
}