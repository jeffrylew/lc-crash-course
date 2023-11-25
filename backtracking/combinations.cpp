#include <gtest/gtest.h>

#include <vector>

static std::vector<std::vector<int>> combine(int n, int k)
{
    std::vector<std::vector<int>> ans {};
    std::vector<int> curr {};
    backtrack(curr, 1, ans, n, k);
    return ans;
}

static void backtrack(std::vector<int>&              curr,
                      int                            i,
                      std::vector<std::vector<int>>& ans,
                      int                            n,
                      int                            k)
{
    if (static_cast<int>(curr.size()) == k)
    {
        ans.push_back(curr);
        return;
    }

    for (int num = i; num <= n; ++num)
    {
        curr.push_back(num);
        backtrack(curr, num + 1, ans, n, k);
        curr.pop_back();
    }
}
