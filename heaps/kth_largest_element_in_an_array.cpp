#include <gtest/gtest.h>

#include <queue>
#include <vector>

//! @brief First attempt solution to get the kth largest element in the vector
//! @param[in] nums Vector of integers
//! @param[in] k    Defines which largest element to retrieve
//! @return The kth largest element in nums
static int findKthLargestFA(std::vector<int> nums, int k)
{
    //! @details Time complexity O(N + k * log k) where N = nums.size(). O(N) to
    //!          convert nums to a max heap. O(k * log k) for k pops from the
    //!          max heap (technically k - 1 pops).
    //!          Space complexity O(N) since max heap initially stores all ints.
    std::priority_queue<int> maxHeap(nums.cbegin(), nums.cend());

    while (k-- > 1)
    {
        maxHeap.pop();
    }

    return maxHeap.top();
}

TEST(FindKthLargestTest, SampleTest)
{
    EXPECT_EQ(5, findKthLargestFA({3, 2, 1, 5, 6, 4}, 2));

    EXPECT_EQ(4, findKthLargestFA({3, 2, 3, 1, 2, 4, 5, 5, 6}, 4));
}