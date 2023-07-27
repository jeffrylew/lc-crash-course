#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <queue>
#include <utility>
#include <vector>

//! @brief Get k closest integers to x from sorted arr. If ties, keep smaller.
//! @param[in] arr Vector of sorted integers
//! @param[in] k   Number of closest integers to retrieve
//! @param[in] x   Number to find k closest neighbors
//! @return Sorted vector of k closest integers to x. If ties, keep smaller.
static std::vector<int> findClosestElementsDS1(std::vector<int> arr,
                                               int              k,
                                               int              x)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /708/heaps/4641/
    //!
    //!          Time complexity O((N + k) * log k) where N = arr.size().
    //!          The heap never grows beyond k so the push and pop operations
    //!          are O(log k), which are performed N times. Need O(k * log k) at
    //!          the end to sort the output. Note this approach does not exploit
    //!          the fact that the input array is sorted and is slower than
    //!          other approaches.
    //!          Space complexity O(k) for the heap.

    //! Want minimum differences so store in a max heap. Pop removes largest
    //! elements. Additionally, ties are handled automatically. If have a max
    //! heap with (5, 3) and (5, 13), a max heap will pop (5, 13) before (5, 3)
    std::priority_queue<std::pair<int, int>> maxHeap {};

    for (const int num : arr)
    {
        const int distance {std::abs(x - num)};
        maxHeap.emplace(distance, num);

        if (static_cast<int>(maxHeap.size()) > k)
        {
            maxHeap.pop();
        }
    }

    std::vector<int> ans {};
    while (not maxHeap.empty())
    {
        ans.push_back(maxHeap.top().second);

        maxHeap.pop();
    }

    std::sort(ans.begin(), ans.end());

    return ans;

} // static std::vector<int> findClosestElementsDS1( ...

TEST(FindClosestElementsTest, SampleTest1)
{
    const std::vector<int> input {1, 2, 3, 4, 5};
    const std::vector<int> expected_output {1, 2, 3, 4};

    EXPECT_EQ(expected_output, findClosestElementsDS1(input, 4, 3));
    EXPECT_EQ(expected_output, findClosestElementsDS1(input, 4, -1));
}
