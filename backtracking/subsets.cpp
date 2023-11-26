#include <gtest/gtest.h>

#include <vector>

//! @brief Recursive helper to get subsets in [i, N)
//! @param[in, out] curr Reference to current subset
//! @param[in]      i    Index of iteration start to avoid duplicates
//! @param[out]     ans  Reference to vector of subsets in [i, N)
//! @param[in]      nums Reference to vector of unique ints
static void backtrack(std::vector<int>&              curr,
                      int                            i,
                      std::vector<std::vector<int>>& ans,
                      const std::vector<int>&        nums)
{
    const auto nums_size = static_cast<int>(nums.size());
    if (i > nums_size)
    {
        //! Have run out of numbers to use
        //! @note Base case is never hit since function can't be called with an
        //!       argument greater than nums.size() but is included for clarity
        return;
    }

    //! A subset can have any length so every node is an answer (even the root,
    //! which represents the empty subset). First thing to do at each node is
    //! add curr to the answer.
    ans.push_back(curr);
    for (int j = i; j < nums_size; ++j)
    {
        curr.push_back(nums[j]);
    
        //! Pass in index of number we are adding plus one to ensure we only
        //! inclue numbers after the one we are adding for the rest of subtree
        backtrack(curr, j + 1, ans, nums);
        curr.pop_back();
    }
}

//! @brief Get all subsets of nums in any order without duplicates
//! @param[in] nums Vector of unique ints
//! @return Vector of all subsets
std::vector<std::vector<int>> subsets(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/subsets/description/
    //!
    //!          Time complexity O(N * 2^N) where N = nums.size(). For each
    //!          element, can either take it or not. Algorithm is a DFS on tree
    //!          with 2^N nodes. At each node, make copy of curr for O(N * 2^N).
    //!          Space complexity O(N) for curr and recursion call stack.

    std::vector<std::vector<int>> ans {};
    std::vector<int>              curr {};
    backtrack(curr, 0, ans, nums);
    return ans;
}

TEST(SubsetsTest, SampleTest1)
{
    const std::vector<std::vector<int>> expected_output {
        {}, {1}, {1, 2}, {1, 2, 3}, {1, 3}, {2}, {2, 3}, {3}};

    EXPECT_EQ(expected_output, subsets({1, 2, 3}));
}
