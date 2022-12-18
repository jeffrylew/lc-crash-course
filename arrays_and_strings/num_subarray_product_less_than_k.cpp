#include <gtest/gtest.h>

#include <cmath>
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

//! @brief Second discussion solution using binary search on logarithms
//! @param[in] nums Vector of integers
//! @param[in] k    Maximum product in a subarray
//! @return Number of subarrays where product of all elements is less than k
static int DS2_binary_search_on_logs(std::vector<int> nums, int k)
{
    //! @details https://leetcode.com/problems/subarray-product-less-than-k/
    //!          solutions/127670/subarray-product-less-than-k/
    //!
    //!          Motivation is product of subarray could be too large so reduce
    //!          problem to subarray sums instead of products through
    //!          ln(x0 * x1 * ...) = ln(x0) + ln(x1) + ... (could use log10 too)
    //!
    //!          Get prefix sums prefix[i+1] = ln(nums[0]) + ln(nums[1]) + ...
    //!          + ln(nums[i]) and find the largest j for each i such that
    //!          ln(nums[i]) + ... + ln(nums[j]) = prefix[j] - prefix[i] < ln(k)
    //!          where prefix[j] < prefix[i] + ln(k) - tolerance (1.0e-9)
    //!          prefix is a monotone increasing array so solve with binary
    //!          search and add width of interval [i, j] to answer, which counts
    //!          all subarrays [i, k] with k <= j
    //!
    //!          Time complexity O(N log N) where N = nums.size(). Inside for
    //!          loop, each binary search takes O(log N)
    //!          Space complexity O(N) for the space used by prefix

    if (k == 0)
    {
        return 0;
    }

    //! Arbitrarily use natural logarithm
    const double logk {std::log(static_cast<double>(k))};

    std::vector<double> prefix(nums.size() + 1ULL);
    const auto          prefix_size = static_cast<int>(prefix.size());

    for (int i = 0; i < static_cast<int>(nums.size()); ++i)
    {
        prefix[i + 1] = prefix[i] + std::log(static_cast<double>(nums[i]));
    }

    int num_subarrays {};
    for (int i = 0; i < prefix_size; ++i)
    {
        int lo {i + 1};
        int hi {prefix_size};

        while (lo < hi)
        {
            int mid {lo + (hi - lo) / 2};

            if (prefix[mid] < prefix[i] + logk - 1.0e-9)
            {
                //! Condition satisfied, check if there is a larger j = mid
                //! while lo is still less than hi
                lo = mid + 1;
            }
            else
            {
                //! prefix[j = mid] is too large
                hi = mid;
            }
        }

        //! lo = mid + 1 so num_subarrays adds mid - i
        num_subarrays += lo - i - 1;

    } // for (int i = 0; ...

    return num_subarrays;

} // static int DS2_binary_search_on_logs( ...

TEST(NumSubarrayProductLessThanKTest, SampleTest)
{
    EXPECT_EQ(8, numSubarrayProductLessThanK({10, 5, 2, 6}, 100));
    EXPECT_EQ(0, numSubarrayProductLessThanK({1, 2, 3}, 0));

    EXPECT_EQ(8, DS2_binary_search_on_logs({10, 5, 2, 6}, 100));
    EXPECT_EQ(0, DS2_binary_search_on_logs({1, 2, 3}, 0));
}