#include <gtest/gtest.h>

#include <vector>

static void backtrack(std::vector<int>&              curr,
                      int                            i,
                      std::vector<std::vector<int>>& ans,
                      const std::vector<int>&        nums)
{
    const auto nums_size = static_cast<int>(nums.size());
    if (i > nums_size)
    {
        return;
    }

    ans.push_back(curr);
    for (int j = i; j < nums_size; ++j)
    {
        curr.push_back(nums[j]);
        backtrack(curr, j + 1, ans, nums);
        curr.pop_back();
    }
}

std::vector<std::vector<int>> subsets(std::vector<int> nums)
{
    std::vector<std::vector<int>> ans {};
    std::vector<int>              curr {};
    backtrack(curr, 0, ans, nums);
    return ans;
}
