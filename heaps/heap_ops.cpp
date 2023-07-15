#include <gtest/gtest.h>

#include <queue>
#include <vector>

TEST(HeapOpsTest, SampleTest)
{
    //! Default is max heap
    std::priority_queue<int> heap;

    //! Add to heap
    heap.push(1);
    heap.push(2);
    heap.push(3);

    //! Check max element
    EXPECT_EQ(3, heap.top());

    //! Pop max element
    heap.pop();

    //! Get size
    EXPECT_EQ(2ULL, heap.size());

    //! Convert vector into heap in linear time
    std::vector<int>         nums {67, 341, 234, -67, 12, -976};
    std::priority_queue<int> heap_from_vec(nums.begin(), nums.end());
    EXPECT_EQ(nums.size(), heap_from_vec.size());

    heap_from_vec.push(7451);
    heap_from_vec.push(-5352);

    //! Numbers will be printed in sorted order
    EXPECT_EQ(7451, heap_from_vec.top());
    heap.pop();

    EXPECT_EQ(341, heap_from_vec.top());
    heap.pop();

    EXPECT_EQ(234, heap_from_vec.top());
    heap.pop();

    EXPECT_EQ(67, heap_from_vec.top());
    heap.pop();

    EXPECT_EQ(12, heap_from_vec.top());
    heap.pop();

    EXPECT_EQ(-67, heap_from_vec.top());
    heap.pop();

    EXPECT_EQ(-976, heap_from_vec.top());
    heap.pop();

    EXPECT_EQ(-5352, heap_from_vec.top());
    heap.pop();

    EXPECT_TRUE(heap_from_vec.empty());
}