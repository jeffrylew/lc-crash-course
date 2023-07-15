#include <gtest/gtest.h>

#include <queue>
#include <vector>

//! @brief Get weight of last remaining stone or 0 if there are no stones left
//! @param[in] stones Vector where stones[i] is weight of ith stone
//! @return Weight of last remaining stone or 0 if there are no stones left
static int lastStoneWeight(std::vector<int> stones)
{
    //! @details https://leetcode.com/problems/last-stone-weight/
    
    std::priority_queue<int> heap(stones.begin(), stones.end());

    while (heap.size() > 1ULL)
    {
        const int first {heap.top()};
        heap.pop();

        const int second {heap.top()};
        heap.pop();

        if (first != second)
        {
            heap.push(first - second);
        }
    }

    return heap.empty() ? 0 : heap.top();
}

TEST(LastStoneWeightTest, SampleTest)
{
    EXPECT_EQ(1, lastStoneWeight({2, 7, 4, 1, 8, 1}));

    EXPECT_EQ(1, lastStoneWeight({1}));
}