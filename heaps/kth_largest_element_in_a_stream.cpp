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

TEST(KthLargestTest, SampleTest)
{
    KthLargestFA testFA {3, {4, 5, 8, 2}};

    EXPECT_EQ(4, testFA.add(3));
    EXPECT_EQ(5, testFA.add(5));
    EXPECT_EQ(5, testFA.add(10));
    EXPECT_EQ(8, testFA.add(9));
    EXPECT_EQ(8, testFA.add(4));
}