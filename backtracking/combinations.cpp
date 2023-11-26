#include <gtest/gtest.h>

#include <vector>

//! @brief Recursive helper function to find all combinations of size k
//! @param[in, out] curr Vector for current combination under consideration
//! @param[in]      i    Starting number to consider in range [i, n]
//! @param[out]     ans  Reference to vector of combination vectors of size k
//! @param[in]      n    Ending number to consider in range [i, n]
//! @param[in]      k    Size of combination
static void backtrack(std::vector<int>&              curr,
                      int                            i,
                      std::vector<std::vector<int>>& ans,
                      int                            n,
                      int                            k)
{
    if (static_cast<int>(curr.size()) == k)
    {
        //! Don't need to continue adding numbers to curr after size k
        //! Leaves represent the base case and are the answer nodes
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

//! @brief Get all combinations of k numbers out of the range [1, n]
//! @param[in] n Number of integers in range [1, n]
//! @param[in] k Size of combinations to select from [1, n]
//! @return All combinations of k numbers out of the range [1, n]
static std::vector<std::vector<int>> combine(int n, int k)
{
    //! @details https://leetcode.com/problems/combinations/description/
    //!
    //!          Exact time complexity is O(k * n! / ((n - k)! * k!)). A good
    //!          strategy is to find the upper bound. On the first call, the for
    //!          loop runs n times. The next call can run n - 1 times, etc. This
    //!          leads to O(n!). However, the max depth is k which means the
    //!          factorial's multiplication doesn't go down to 1. It goes to
    //!          n - k so we need to divide the factorial by (n - k)!.
    //!          Copying each combination costs O(k) so this approximation gives
    //!          O(k * n! / (n - k)!).
    //!          Space complexity O(k) for curr and the recursion call stack.

    std::vector<std::vector<int>> ans {};
    std::vector<int>              curr {};

    //! Initially, i = 1 indicates we are considering 1 and all numbers after it
    backtrack(curr, 1, ans, n, k);
    return ans;
}

TEST(CombineTest, SampleTest1)
{
    const std::vector<std::vector<int>> expected_output {
        {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}};

    EXPECT_EQ(expected_output, combine(4, 2));
}
