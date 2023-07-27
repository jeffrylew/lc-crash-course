#include <gtest/gtest.h>

#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

//! @brief Get k most frequent elements from vector of ints nums
//! @param[in] nums Vector of integers
//! @param[in] k    Number of most frequent elements
//! @return k most frequent elements from nums
static std::vector<int> topKFrequent(std::vector<int> nums, int k)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /708/heaps/4641/
    //!
    //!          Time complexity O(N * log k) where N = nums.size(). Counting
    //!          frequencies only costs O(N). In the main loop, iterate N times
    //!          and perform heap operations. The size of the heap never exceeds
    //!          k so each iteration costs O(log k).
    //!          Space complexity O(k) for the heap

    std::unordered_map<int, int> counts {};
    for (const int num : nums)
    {
        ++counts[num];
    }

    std::priority_queue<std::pair<int, int>> minHeap {};
    for (const auto [key, val] : counts)
    {
        minHeap.emplace(-val, key);
        if (static_cast<int>(minHeap.size()) > k)
        {
            minHeap.pop();
        }
    }

    std::vector<int> ans {};
    while (not minHeap.empty())
    {
        ans.push_back(minHeap.top().second);
        minHeap.pop();
    }

    return ans;
}

TEST(TopKFrequentTest, SampleTest1)
{
    const std::vector<int> expected_output {1, 2};

    EXPECT_EQ(expected_output, topKFrequent({1, 1, 1, 2, 2, 3}, 2));
}

TEST(TopKFrequentTest, SampleTest2)
{
    const std::vector<int> expected_output {1};

    EXPECT_EQ(expected_output, topKFrequent({1}, 1));
}