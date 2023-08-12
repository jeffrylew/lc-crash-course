#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Get min number of subsequences needed to partition nums
//! @param[in] nums Vector to split into subsequences where |max - min| <= k
//! @param[in] k    Max and min elements in subsequence must differ by k at most
//! @return Min number of subsequences to partition nums
static int partitionArray(std::vector<int> nums, int k)
{
    //! @details https://leetcode.com/problems/
    //!          partition-array-such-that-maximum-difference-is-k/
    //!
    //!          Time complexity O(N * log N) where N = nums.size() for sorting
    //!          Space complexity likely O(log N) due to quicksort variation use

    std::sort(nums.begin(), nums.end());

    int ans {1};
    int x {nums[0]};

    for (int i = 1; i < static_cast<int>(nums.size()); ++i)
    {
        if (nums[i] - x > k)
        {
            x = nums[i];
            ++ans;
        }
    }

    return ans;
}

TEST(PartitionArrayTest, SampleTest)
{
    EXPECT_EQ(2, partitionArray({3, 6, 1, 2, 5}, 2));
}