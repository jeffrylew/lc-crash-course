#include <gtest/gtest.h>

#include <functional>
#include <vector>

//! @brief Get all unique combinations of candidates whose sum is target
//! @param[in] candidates Vector of distinct positive integers
//! @param[in] target     The target sum
//! @return Vector of all unique combinations of candidates whose sum is target
static std::vector<std::vector<int>> combinationSum(std::vector<int> candidates,
                                                    int              target)
{
    //! @details https://leetcode.com/problems/combination-sum/
    //!
    //!          Time complexity O(n ^ (T / M)) where n = candidates.size(),
    //!          T = target, and M = min(candidates). The max depth of the
    //!          recursive tree is T / M when the smallest number is repeatedly
    //!          used until target is exceeded. Each node in the tree can have
    //!          up to n children, giving O(n ^ (T / M)).
    //!          Space complexity O(T / M) for path and the recursion call stack

    std::vector<std::vector<int>> ans {};
    std::vector<int>              path {};

    std::function<void(int, int)> backtrack = [&](int start, int curr) {
        if (curr == target)
        {
            ans.push_back(path);
            return;
        }

        for (int i = start; i < static_cast<int>(candidates.size()); ++i)
        {
            const int num {candidates[i]};

            if (curr + num <= target)
            {
                path.push_back(num);
                backtrack(i, curr + num);
                path.pop_back();
            }
        }
    };

    backtrack(0, 0);
    return ans;
}

TEST(CombinationSumTest, SampleTest)
{
    const std::vector<std::vector<int>> expected_output {{2, 2, 3}, {7}};

    EXPECT_EQ(expected_output, combinationSum({2, 3, 6, 7}, 7));
}
