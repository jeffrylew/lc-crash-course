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

//! @brief Discussion solution: Sort with custom comparator
//! @param[in] arr Vector of sorted integers
//! @param[in] k   Number of closest integers to retrieve
//! @param[in] x   Number to find k closest neighbors
//! @return Sorted vector of k closest integers to x. If ties, keep smaller.
static std::vector<int> findClosestElementsDS2(std::vector<int> arr,
                                               int              k,
                                               int              x)
{
    //! @details https://leetcode.com/problems/find-k-closest-elements/editorial
    //!
    //!          Time complexity O(N * log N + k * log k) where N = arr.size().
    //!          Initially sorting every element in arr with a custom comparator
    //!          costs O(N * log N). The final sorting costs O(k * log k) since
    //!          result.size() is k.
    //!          Space complexity O(N). If arr had to be copied into sortedArr
    //!          then it would contain every element. However, we sort the input
    //!          in-place so we are using less space (O(k)).

    //! Sort using custom comparator
    //! If input arr is passed by reference then copy it first, e.g.
    //!     auto sortedArr = arr;
    std::sort(arr.begin(), arr.end(), [=](int lhs, int rhs) -> bool {
        if (std::abs(lhs - x) == std::abs(rhs - x))
        {
            return lhs < rhs;
        }

        return std::abs(lhs - x) < std::abs(rhs - x);
    });

    //! Only take k elements
    std::vector<int> result(k);
    std::copy_n(arr.cbegin(), k, result.begin());

    //! Sort again to have output in ascending order
    std::sort(result.begin(), result.end());
    return result;

} // static std::vector<int> findClosestElementsDS2( ...

//! @brief Discussion solution: Binary search + sliding window
//! @param[in] arr Vector of sorted integers
//! @param[in] k   Number of closest integers to retrieve
//! @param[in] x   Number to find k closest neighbors
//! @return Sorted vector of k closest integers to x. If ties, keep smaller.
static std::vector<int> findClosestElementsDS3(std::vector<int> arr,
                                               int              k,
                                               int              x)
{
    //! @details https://leetcode.com/problems/find-k-closest-elements/editorial
    //!
    //!          Time complexity O(log N + k) where N = arr.size(). The initial
    //!          binary search to find where to start the window costs O(log N).
    //!          The sliding window initially starts with size 0 and expands one
    //!          by one until it is of size k so it costs O(k) to expand it.
    //!          Space complexity O(1). Only use integers left and right. Space
    //!          used for the output is not counted towards the space complexity

    //! Base case
    if (static_cast<int>(arr.size()) == k)
    {
        return arr;
    }

    //! Binary search to find the closest element
    int  left {};
    int  mid {};
    auto right = static_cast<int>(arr.size());

    while (left < right)
    {
        mid = (left + right) / 2;

        if (arr[mid] >= x)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    //! Initialize sliding window bounds
    --left;
    right = left + 1;

    //! While the window size is less than k
    while (right - left - 1 < k)
    {
        //! Be careful to not go out of bounds
        if (left == -1)
        {
            ++right;
            continue;
        }

        //! Expand the windows towards the side with the closer number
        //! Be careful to not go out of bounds with the pointers
        if (right == static_cast<int>(arr.size())
            || std::abs(arr[left] - x) <= std::abs(arr[right] - x))
        {
            --left;
        }
        else
        {
            ++right;
        }
    }

    //! Build and return the window
    std::vector<int> result(k);

    std::copy_n(arr.begin() + left + 1, k, result.begin());

    return result;

} // static std::vector<int> findClosestElementsDS3( ...

TEST(FindClosestElementsTest, SampleTest1)
{
    const std::vector<int> input {1, 2, 3, 4, 5};
    const std::vector<int> expected_output {1, 2, 3, 4};

    EXPECT_EQ(expected_output, findClosestElementsDS1(input, 4, 3));
    EXPECT_EQ(expected_output, findClosestElementsDS1(input, 4, -1));

    EXPECT_EQ(expected_output, findClosestElementsDS2(input, 4, 3));
    EXPECT_EQ(expected_output, findClosestElementsDS2(input, 4, -1));

    EXPECT_EQ(expected_output, findClosestElementsDS3(input, 4, 3));
    EXPECT_EQ(expected_output, findClosestElementsDS3(input, 4, -1));
}
