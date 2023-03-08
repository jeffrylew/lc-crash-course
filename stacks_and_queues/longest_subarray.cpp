#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <vector>

static int longestSubarray(std::vector<int> nums, int limit)
{
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