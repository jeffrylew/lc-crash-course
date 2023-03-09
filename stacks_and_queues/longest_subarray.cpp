#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <vector>

//! @brief Get size of longest subarray such that absolute diff is <= limit
//! @param[in] nums  Vector of integers
//! @param[in] limit Absolute difference between any two elements must be <= lim
//! @return Size of longest non-empty subarray
static int longestSubarray(std::vector<int> nums, int limit)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /706/stacks-and-queues/4517/
    //!
    //!          Time complexity O(N) where N is the size of nums. Each for loop
    //!          iteration is amortized O(N)
    //!          Space complexity O(N) since the deques can grow to size N

    std::deque<int> increasing;
    std::deque<int> decreasing;
    int left {};
    int ans {};

    for (int right = 0; right < nums.size(); ++right)
    {
        while (!increasing.empty() && increasing.back() > nums[right])
        {
            increasing.pop_back();
        }
        while (!decreasing.empty() && decreasing.back() < nums[right])
        {
            decreasing.pop_back();
        }

        increasing.push_back(nums[right]);
        decreasing.push_back(nums[right]);

        while (decreasing.front() - increasing.front() > limit)
        {
            if (nums[left] == decreasing.front())
            {
                decreasing.pop_front();
            }
            if (nums[left] == increasing.front())
            {
                increasing.pop_front();
            }

            ++left;
        }

        ans = std::max(ans, right - left + 1);
    }

    return ans;
}

TEST(LongestSubarrayTest, TestCase1)
{
    EXPECT_EQ(2, longestSubarray({8, 2, 4, 7}, 4));
}

TEST(LongestSubarrayTest, TestCase2)
{
    EXPECT_EQ(4, longestSubarray({10, 1, 2, 4, 7, 2}, 5));
}

TEST(LongestSubarrayTest, TestCase3)
{
    EXPECT_EQ(3, longestSubarray({4, 2, 2, 2, 4, 4, 2, 2}, 0));
}