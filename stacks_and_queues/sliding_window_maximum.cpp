#include <gtest/gtest.h>

#include <deque>
#include <vector>

//! @brief For each sliding window of size k find the max element
//! @param[in] nums Vector of integers
//! @param[in] k    Size of sliding window
//! @return Vector of max elements in nums
static std::vector<int> maxSlidingWindow(std::vector<int> nums, int k)
{
    std::vector<int> ans {};
    std::deque<int>  deque {};

    for (int i = 0; i < nums.size(); ++i)
    {
        while (not deque.empty() && nums[i] > nums[deque.back()])
        {
            deque.pop_back();
        }

        deque.push_back(i);

        if (deque.front() + k == i)
        {
            deque.pop_front();
        }

        if (i >= k - 1)
        {
            ans.push_back(nums[deque.front()]);
        }
    }

    return ans;
}

TEST(MaxSlidingWindowTest, TestCase1)
{
    const std::vector<int> input {1, 3, -1, -3, 5, 3, 6, 7};
    const std::vector<int> expected_output {3, 3, 5, 5, 6, 7};

    EXPECT_EQ(expected_output, maxSlidingWindow(input, 3));
}

TEST(MaxSlidingWindowTest, TestCase2)
{
    const std::vector<int> input {1};
    const std::vector<int> expected_output {1};

    EXPECT_EQ(expected_output, maxSlidingWindow(input, 1));
}