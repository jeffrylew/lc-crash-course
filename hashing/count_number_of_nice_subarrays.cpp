#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>

//! @brief Find number of subarrays with exactly k odd numbers in them
//! @param[in] nums Vector of positive integers
//! @param[in] k    Number of odd integers
//! @return Number of subarrays with k odd numbers
static int numberOfSubarrays(std::vector<int> nums, int k)
{
    //! Map of <odd number count, number of subarrays containing count>
    std::unordered_map<int, int> counts {};

    //! Initialize empty subarray (zero odd numbers) with frequency of 1
    counts[0] = 1;

    //! Output number of subarrays with k odd numbers
    int ans {};

    //! Keep track of number of odd numbers
    int curr {};

    for (const int num : nums)
    {
        curr += (num % 2);
        ans += counts[curr - k];
        ++counts[curr];
    }

    return ans;

} // static int numberOfSubarrays( ...

TEST(NumberOfSubarraysTest, SampleTest)
{
    //! idx:  [0, 1, 2, 3, 4]
    //! nums: [1, 1, 2, 1, 1], k = 3
    //!
    //! idx 0: curr = 1
    //!        ans = counts[1 - 3] = 0
    //!        counts[0] = 1, counts[1] = 1
    //! idx 1: curr = 2
    //!        ans = counts[2 - 3] = 0
    //!        counts[0] = 1, counts[1] = 1, counts[2] = 1
    //! idx 2: curr = 2
    //!        ans = 0
    //!        counts[0] = 1, counts[1] = 1, counts[2] = 2
    //! idx 3: curr = 3
    //!        ans = counts[3 - 3] = 1
    //!        counts[0] = 1, counts[1] = 1, counts[2] = 2, counts[3] = 1
    //! idx 4: curr = 4
    //!        ans += counts[4 - 3] = 2; At idx i = 4, the number of odd numbers
    //!        up to i is curr = 4. There is an idx j = 0 where number of odd
    //!        numbers up to j is curr - k = 4 - 3 = 1. Thus, the number of odd
    //!        numbers in subarray from (j, i] = (0, 4] = curr - (curr - k) = k.
    //!        counts[0] = 1, counts[1] = 1, counts[2] = 2,
    //!        counts[3] = 1, counts[4] = 1
    EXPECT_EQ(2, numberOfSubarrays({1, 1, 2, 1, 1}, 3));
}