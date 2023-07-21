#include <gtest/gtest.h>

#include <cassert>
#include <functional>
#include <queue>
#include <vector>

//! @class KthLargestFA
//! @brief First attempt to find kth largest element in a stream
class KthLargestFA
{
    int k_ {};

    std::priority_queue<int>                                      maxHeap_;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap_;

public:
    KthLargestFA(int k, std::vector<int> nums)
        : k_(k)
        , maxHeap_(nums.cbegin(), nums.cend())
    {
        //! Problem states it is guaranteed that there will be at least
        //! k elements when you search for the kth element. Thus, nums must have
        //! a minimum size of k - 1 since the first call to add will increase it
        assert(k - 1 <= static_cast<int>(nums.size()));
    }
    
    //! @brief Append val to stream and return kth largest element
    //! @param[in] val Integer to add to stream
    //! @return kth largest element in the stream
    int add(int val)
    {
        maxHeap_.push(val);

        while (minHeap_.size() < k_)
        {
            minHeap_.push(maxHeap_.top());
            maxHeap_.pop();
        }

        //! minHeap_ may already have size() == k_ so ensure it only contains
        //! the kth largest elements
        if (not maxHeap_.empty())
        {
            minHeap_.push(maxHeap_.top());
            maxHeap_.pop();

            maxHeap_.push(minHeap_.top());
            minHeap_.pop();
        }

        return minHeap_.top();
    }
};

//! @class KthLargestDS
//! @brief Discussion solution to find kth largest element in a stream
//! @details leetcode.com/problems/kth-largest-element-in-a-stream/editorial/
//!
//!          Time complexity O(N * log(N) + M * log(k)) where N is nums.size()
//!          and M is the number of calls to add(). The constructor initially
//!          converts nums into a heap of size N costing O(N). Then, need to
//!          remove from heap until there are only k elements (remove N - k).
//!          In the worst case, these removals take O(N) operations when k = 1.
//!          Each operation costs log(N) so the constructor costs
//!          O(N + N * log(N)) = O(N * log(N)). Next, each call to add involves
//!          adding and potentially removing an element from minHeap_. Since our
//!          heap is of size k, the worst case costs O(2 * log(k)) = O(log(k)).
//!          M calls to add() costs O(M * log(k)).
//!          Space complexity O(N). During the add() calls the heap size is k
//!          but in the constructor it initially has size N during conversion.
class KthLargestDS
{
    int k_ {};

    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap_;

public:
    KthLargestDS(int k, std::vector<int> nums)
        : k_(k)
        , minHeap_(nums.cbegin(), nums.cend())
    {
        while (static_cast<int>(minHeap_.size()) > k)
        {
            minHeap_.pop();
        }
    }
    
    //! @brief Append val to stream and return kth largest element
    //! @param[in] val Integer to add to stream
    //! @return kth largest element in the stream
    int add(int val)
    {
        minHeap_.push(val);

        if (static_cast<int>(minHeap_.size()) > k_)
        {
            minHeap_.pop();
        }

        return minHeap_.top();
    }
};

TEST(KthLargestTest, SampleTest)
{
    KthLargestFA testFA {3, {4, 5, 8, 2}};

    EXPECT_EQ(4, testFA.add(3));
    EXPECT_EQ(5, testFA.add(5));
    EXPECT_EQ(5, testFA.add(10));
    EXPECT_EQ(8, testFA.add(9));
    EXPECT_EQ(8, testFA.add(4));

    KthLargestDS testDS {3, {4, 5, 8, 2}};

    EXPECT_EQ(4, testDS.add(3));
    EXPECT_EQ(5, testDS.add(5));
    EXPECT_EQ(5, testDS.add(10));
    EXPECT_EQ(8, testDS.add(9));
    EXPECT_EQ(8, testDS.add(4));
}