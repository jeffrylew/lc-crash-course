#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <unordered_map>
#include <vector>

//! @brief Find length of shortest subarray containing at least one duplicate
//! @param[in] cards Vector of ints potentially containing duplicates
//! @return Length of shortest subarray containing at least one duplicate
static int minimumCardPickup1(std::vector<int> cards)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /705/hashing/4645/
    //!
    //!          Time complexity O(N) since inner nested loop can only iterate
    //!          N times in total over indices of elements from the vector,
    //!          where N = cards.size()
    //!          Space complexity O(N)

    std::unordered_map<int, std::vector<int>> dic {};

    for (int i = 0; i < static_cast<int>(cards.size()); ++i)
    {
        dic[cards[i]].push_back(i);
    }

    int ans {std::numeric_limits<int>::max()};
    /*
    for (auto [key, arr] : dic)
    */
    for (const auto& kv : dic)
    {
        const auto arr_size = static_cast<int>(kv.second.size());
        for (int i = 1; i < arr_size; ++i)
        {
            ans = std::min(ans, arr[i] - arr[i - 1] + 1);
        }
    }

    return ans == std::numeric_limits<int>::max() ? -1 : ans;

} // static int minimumCardPickup1( ...

TEST(MinimumCardPickupTest, SampleTest)
{
    EXPECT_EQ(2, minimumCardPickup1({1, 2, 6, 2, 1}));
}