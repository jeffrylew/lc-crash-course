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
    //! @details First attempt solution does not pass SampleTest3
    //!          24 / 31 test cases passed

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
    
        int idx {};
        while (idx < static_cast<int>(nums.size()))
        {
            current_subarray_sum += nums[idx];

            if (current_subarray_sum >= min_subarray_sum)
            {
                if (++num_subarrays == k)
                {
                    //! k subarrays reached, add remaining elements in nums
                    current_subarray_sum +=
                        std::accumulate(nums.begin() + idx + 1, nums.end(), 0);
                    largest_subarray_sum =
                        std::max(largest_subarray_sum, current_subarray_sum);
                    break;
                }

                largest_subarray_sum =
                  std::max(largest_subarray_sum, current_subarray_sum);
                current_subarray_sum = 0;
            }

            ++idx;
        }

        if (num_subarrays == k)
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

//! @brief DS1 recursive helper for recurrence relation F[currIdx, subarrCount]
//! @param[in, out] memo        2D vector for min largest sum memoization 
//! @param[in, out] prefixSum   Vector containing prefix sum of nums
//! @param[in]      currIdx     Beginning index of current subarray
//! @param[in]      subarrCount Number of subarrays
//! @return Min largest subarr sum for [currIdx, N-1] with subarrCount subarrays
static int getMinimumLargestSplitSum(std::vector<std::vector<int>>& memo,
                                     std::vector<int>&              prefixSum,
                                     int                            currIdx,
                                     int                            subarrCount)
{
    const auto nums_size = static_cast<int>(prefixSum.size()) - 1;

    //! Already calculated the answer so no need to recurse
    if (memo[currIdx][subarrCount] != -1)
    {
        return memo[currIdx][subarrCount];
    }

    //! Base Case: If there is only one subarray left then all remaining numbers
    //! must go into current subarray. Return sum of remaining numbers
    if (subarrCount == 1)
    {
        memo[currIdx][subarrCount] = prefixSum[nums_size] - prefixSum[currIdx];
        return memo[currIdx][subarrCount];
    }

    //! Otherwise, use recurrence relation to determine the min largest subarray
    //! sum between currIdx and end of nums with subarrCount subarrays remaining
    int minimumLargestSplitSum {std::numeric_limits<int>::max()};
    for (int i = currIdx; i <= nums_size - subarrCount; ++i)
    {
        //! Store the sum of the first subarray
        const int firstSplitSum {prefixSum[i + 1] - prefixSum[currIdx]};

        //! Find the maximum subarray sum for the current first split
        const int largestSplitSum {
            std::max(getMinimumLargestSplitSum(
                memo, prefixSum, i + 1, subarrCount - 1),
            firstSplitSum)};

        //! Find the minimum among all possible combinations
        minimumLargestSplitSum =
            std::min(minimumLargestSplitSum, largestSplitSum);

        if (firstSplitSum >= minimumLargestSplitSum)
        {
            break;
        }
    }

    return memo[currIdx][subarrCount] = minimumLargestSplitSum;

} // static int getMinimumLargestSplitSum( ...

//! @brief Split nums into k non-empty subarrays so largest sum is minimized
//! @param[in] nums Vector of ints
//! @param[in] k    Number of non-empty subarrays to split
//! @return Minimized largest sum of the split
static int splitArrayDS1(std::vector<int> nums, int k)
{
    //! @details https://leetcode.com/problems/split-array-largest-sum/editorial
    //!
    //!          Top-Down Dynamic Programming discussion solution
    //!          Time complexity O(N^2 * k) where N = nums.size() and k = number
    //!          of subarrays allowed (= M in discussion solution). Each state
    //!          is defined by the values currIdx and subarrCount. There are
    //!          N * k possible states and we must visit almost every state to
    //!          solve the original problem. Each state (subproblem) requires
    //!          O(N) time due to a for loop from currIdx to N - subarrCount.
    //!          Space complexity O(N * k). Memoization results are stored in
    //!          the table memo of size N * k. Also, the recursion stack space
    //!          is equal to the maximum number of active functions, which can
    //!          be equal to k since we only make a recursive call when
    //!          splitting the vector and we do not make a recursive call when
    //!          there is only 1 subarray remaining.

    //! 2D vector for memoization defined with NROWS = maximum nums.size() and
    //! NCOLS = maximum split/subarray count k = min(50, nums.size())
    constexpr int NROWS {1001};
    constexpr int NCOLS {51};

    //! Initialize with -1 so can differentiate if already calculated answer
    //! memo[index in nums][subarray count]
    std::vector<std::vector<int>> memo(NROWS, std::vector<int>(NCOLS, -1));

    //! Store prefix sum of nums array
    const auto       nums_size = static_cast<int>(nums.size());
    std::vector<int> prefixSum(nums_size + 1);
    for (int i = 0; i < nums_size; ++i)
    {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    return getMinimumLargestSplitSum(memo, prefixSum, 0, k);
}

TEST(SplitArrayTest, SampleTest1)
{
    const std::vector<int> nums {7, 2, 5, 10, 8};

    EXPECT_EQ(18, splitArrayFA(nums, 2));
    EXPECT_EQ(18, splitArrayDS1(nums, 2));
}

TEST(SplitArrayTest, SampleTest2)
{
    const std::vector<int> nums {1, 2, 3, 4, 5};

    EXPECT_EQ(9, splitArrayFA(nums, 2));
    EXPECT_EQ(9, splitArrayDS1(nums, 2));
}

TEST(SplitArrayTest, SampleTest3)
{
    const std::vector<int> nums {
        10, 5, 13, 4, 8, 4, 5, 11, 14, 9, 16, 10, 20, 8
    };

    EXPECT_NE(25, splitArrayFA(nums));
    EXPECT_EQ(28, splitArrayFA(nums));
    EXPECT_EQ(25, splitArrayDS1(nums));
}