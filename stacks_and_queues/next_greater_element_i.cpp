#include <gtest/gtest.h>

#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

//! @brief First attempt to get next greater element from nums2 for nums1[i]
//! @param[in] nums1 Vector of integers that is a subset of nums2
//! @param[in] nums2 Vector of integers
//! @return Vector of length nums1 containing next greater elements
static std::vector<int> nextGreaterElementFA(std::vector<int> nums1,
                                             std::vector<int> nums2)
{
    //! @details I know this is incorrect, need to use queue2 somehow...

    std::queue<int> queue2 {};

    int idx1 {};
    int idx2 {};

    while (idx1 < nums1.size())
    {
        while (idx2 < nums2.size() && nums2[idx2] <= nums1[idx1])
        {
            queue2.push(nums2[idx2++]);
        }

        nums1[idx1++] = (idx2 == nums2.size()) ? -1 : nums2[idx2];
    }

    return nums1;

} // static std::vector<int> nextGreaterElementFA( ...

//! @brief Discussion solution to get next greater nums2 element for nums1[i]
//! @param[in] nums1 Vector of integers that is a subset of nums2
//! @param[in] nums2 Vector of integers
//! @return Vector of length nums1 containing next greater elements
static std::vector<int> nextGreaterElementDS(std::vector<int> nums1,
                                             std::vector<int> nums2)
{
    //! @details https://leetcode.com/problems/next-greater-element-i/editorial/
    //!
    //!          Time complexity O(N) where N = nums2.size(). Entire nums2 is
    //!          scanned only. Each of stack's N elements are pushed and popped
    //!          once. nums1 is also scanned only once. Total O(N + N + M) where
    //!          M = nums1.size(). Since num1 is a subset of nums2, M <= N so
    //!          the simplified time complexity is O(N)
    //!          Space complexity O(N). The map stores N key-value pairs while
    //!          the stack contains N elements at most at any given time.

    std::stack<int>              stack {};
    std::unordered_map<int, int> stack_nums2 {};

    for (const auto ele2 : nums2)
    {
        while (not stack.empty() && ele2 > stack.top())
        {
            //! Current element in nums2 is larger than top of stack
            //! Add stack element as key and nums2 element as next greater value
            stack_nums2.emplace(stack.top(), ele2);
            stack.pop();
        }
        stack.push(ele2);
    }

    while (not stack.empty())
    {
        stack_nums2.emplace(stack.top(), -1);
        stack.pop();
    }

    for (int i = 0; i < nums1.size(); ++i)
    {
        nums1[i] = stack_nums2[nums1[i]];
    }

    return nums1;
}

TEST(NextGreaterElementTest, SampleTest)
{
    const std::vector<int> expected_output {-1, 3, -1};
    EXPECT_NE(expected_output, nextGreaterElementFA({4, 1, 2}, {1, 3, 4, 2}));

    EXPECT_EQ(expected_output, nextGreaterElementDS({4, 1, 2}, {1, 3, 4, 2}));
}