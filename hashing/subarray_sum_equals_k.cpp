#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>

static int subarraySum(std::vector<int> nums, int k)
{
    //! @details Assume nums: [1, 2, 1, 2, 1], k = 3
    //!           Prefix sum: [1, 3, 4, 6, 7]
    //!          Then curr = 1, curr - k = 1 - 3 = -2
    //!               curr = 3, curr - k = 3 - 3 = 0
    //!               curr = 4, curr - k = 4 - 3 = 1
    //!               curr = 6, curr - k = 6 - 3 = 3
    //!               curr = 7, curr - k = 7 - 3 = 4
    //!
    //!          Time complexity O(N) where N = nums.size()
    //!          Space complexity O(N) since hash map can grow to N elements

    //! Tracks how many times a prefix sum has occurred, accounting for negative
    //! numbers (if curr is only increasing then a set could be used instead)
    std::unordered_map<int, int> counts {};

    //! Initialize hash map with 0: 1 since empty subarray technically has sum 0
    counts[0] = 1;

    //! Number of subarrays whose sum is equal to k
    int ans {};

    //! Tracks constraint metric for entire prefix at any given point in
    //! iteration, i.e. stores prefix sum where "constraint metric" is sum
    //! At any index i, the sum up to i is curr
    //! If there is index j whose prefix is curr - k then the sum of the
    //! subarray from (j, i] is curr - (curr - k) = k
    int curr {};

    for (int num : nums)
    {
        curr += num;

        //! At every index i, the frequency of curr - k equals the number of
        //! subarrays whose sum is equal to k that end at i
        ans += counts[curr - k];
        ++counts[curr];
    }

    return ans;

} // static int subarraySum( ...

TEST(SubarraySumTest, SampleTest)
{
    EXPECT_EQ(4, subarraySum({1, 2, 1, 2, 1}, 3));
}