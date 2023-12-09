#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Recursive helper to build each permutation in curr
//! @param[in, out] curr Reference to vector containing current permutation
//! @param[out]     ans  Reference to vector containing all permutations
//! @param[in]      nums Reference to vector of distinct integers
static void backtrack(std::vector<int>&              curr,
                      std::vector<std::vector<int>>& ans,
                      const std::vector<int>&        nums)
{
    //! Base case: Completed a permutation, add curr to ans and return
    //! This is a leaf node in the tree of permutations
    if (curr.size() == nums.size())
    {
        //! Returning = moving back up the tree/removing the last node in path
        //! We are copying curr upon pushing
        ans.push_back(curr);
        return;
    }

    //! Loop over entire input on each call to backtrack. To build all
    //! permutations, we need all elements at the first index, and for each of
    //! those elements, we need all other elements at the second index, etc.
    for (const int num : nums)
    {
        //! A permutation cannot have duplicates. Check if a number is already
        //! in curr before adding it to curr
        if (std::find(curr.begin(), curr.end(), num) == curr.end())
        {
            curr.push_back(num);

            //! Each call to backtrack is like a visit to a node in the tree of
            //! possibilities (i.e. moving to a child)
            backtrack(curr, ans, nums);

            //! After returning, need to remove the last element from curr
            curr.pop_back();
        }
    }
}

//! @brief Get all possible permutations of nums
//! @param[in] nums Vector of distinct integers
//! @return Vector of all possible permutations
static std::vector<std::vector<int>> permute(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/permutations/description/
    //!
    //!          Time complexity O(N * N!) where N = nums.size(). The initial
    //!          call to backtrack (root of tree) makes N calls. Each of those
    //!          calls makes N - 1 calls and each of the latter make N - 2, etc.
    //!          The exact time complexity is actually quite complicted but can
    //!          estimate it to be around O(N * N!). The extra factor of N is
    //!          needed to copy each permutation.
    //!          Space complexity O(N) for curr and the recursion call stack.

    std::vector<std::vector<int>> ans {};
    std::vector<int>              curr {};
    backtrack(curr, ans, nums);
    return ans;
}

//! @brief Implementation using a lambda helper function
//! @param[in] nums Vector of distinct integers
//! @return Vector of all possible permutations of nums
static std::vector<std::vector<int>> permute_lambda(std::vector<int> nums)
{
    std::vector<std::vector<int>> ans {};
    std::vector<int>              curr {};

    std::function<void()> backtrack = [&]() {
        if (curr.size() == nums.size())
        {
            ans.push_back(curr);
            return;
        }

        for (const int num : nums)
        {
            if (std::find(curr.cbegin(), curr.cend(), num) == curr.cend())
            {
                curr.push_back(num);
                backtrack();
                curr.pop_back();
            }
        }
    };

    backtrack();
    return ans;
}

TEST(PermuteTest, SampleTest1)
{
    const std::vector<std:vector<int>> expected_output {
        {1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};

    EXPECT_EQ(expected_output, permute({1, 2, 3}));
    EXPECT_EQ(expected_output, permute_lambda({1, 2, 3}));
}

TEST(PermuteTest, SampleTest2)
{
    const std::vector<std::vector<int>> expected_output {{0, 1}, {1, 0}};

    EXPECT_EQ(expected_output, permute({0, 1}));
    EXPECT_EQ(expected_output, permute_lambda({0, 1}));
}

TEST(PermuteTest, SampleTest3)
{
    const std::vector<std::vector<int>> expected_output {{1}};

    EXPECT_EQ(expected_output, permute({1}));
    EXPECT_EQ(expected_output, permute_lambda({1}));
}
