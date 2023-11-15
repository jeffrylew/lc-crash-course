#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

static void backtrack(std::vector<int>&              curr,
                      std::vector<std::vector<int>>& ans,
                      const std::vector<int>&        nums)
{
    if (curr.size() == nums.size())
    {
        ans.push_back(curr);
        return;
    }

    for (const int num : nums)
    {
        if (std::find(curr.begin(), curr.end(), num) == curr.end())
        {
            curr.push_back(num);
            backtrack(curr, ans, nums);
            curr.pop_back();
        }
    }
}

static std::vector<std::vector<int>> permute(std::vector<int> nums)
{
    std::vector<std::vector<int>> ans {};
    std::vector<int>              curr {};
    backtrack(curr, ans, nums);
    return ans;
}