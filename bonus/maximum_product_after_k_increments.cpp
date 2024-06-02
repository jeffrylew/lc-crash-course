#include <gtest/gtest.h>

#include <functional>
#include <queue>
#include <vector>

//! @brief Get max product of nums mod 10^9 + 7 after incrementing k nums by 1
//! @param[in] nums Vector of non-negative integers
//! @param[in] k    Number of elements that can be incremented by 1
//! @return Max product of nums modulus 10^9 + 7 after k operations
static int maximumProduct(std::vector<int> nums, int k)
{
    //! @details leetcode.com/problems/maximum-product-after-k-increments
    //!
    //!          Time complexity O(N * log N) where N = nums.size(). min_heap
    //!          construction is O(N) according to the description of (7) under
    //!        en.cppreference.com/w/cpp/container/priority_queue/priority_queue
    //!          Incrementing k elements by 1 takes O(k * log N) for inserting
    //!          and popping k times. Finally, popping all elements takes
    //!          O(N * log N) for the pop operation according to
    //!          https://en.cppreference.com/w/cpp/container/priority_queue/pop.
    //!          Space complexity O(N) for std::priority_queue.

    std::priority_queue min_heap(nums.begin(), nums.end(), std::greater<int>());

    for (int num_ops = 0; num_ops < k; ++num_ops)
    {
        const int ele {min_heap.top()};
        min_heap.pop();
        min_heap.push(ele + 1);
    }

    constexpr int modulus {1000000000 + 7};
    long long     ans {1};

    while (!min_heap.empty())
    {
        ans = (ans * min_heap.top()) % modulus;
        min_heap.pop();
    }

    return static_cast<int>(ans % modulus);
}

TEST(MaximumProductTest, SampleTest1)
{
    EXPECT_EQ(20, maximumProduct({0, 4}, 5));
}

TEST(MaximumProductTest, SampleTest2)
{
    EXPECT_EQ(216, maximumProduct({6, 3, 3, 2}, 2));
}
