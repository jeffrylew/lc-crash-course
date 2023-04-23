#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <vector>

//! @brief Recursive helper function to get sorted vector of values in tree
//! @param[in] node Pointer to current node in tree
//! @return Vector of values from BST in sorted order
static std::vector<int> dfs(TreeNode* node)
{
    //! @details Time complexity O(N)

    if (node == nullptr)
    {
        return {};
    }

    auto       left  = dfs(node->left);
    const auto right = dfs(node->right);
    left.push_back(node->val);
    left.insert(left.end(), right.begin(), right.end());
    return left;
}

//! @brief Get min abs diff between values of any two nodes in BST
//! @param[in] root Pointer to root of BST
//! @return Minimum absolute difference between values of any two nodes in tree
static int getMinimumDifferenceRecursive(TreeNode* root)
{
    auto values = dfs(root);
    int  ans {std::numeric_limits<int>::max()};
    for (int i = 1; i < static_cast<int>(values.size()); ++i)
    {
        ans = std::min(ans, values[i] - values[i - 1]);
    }

    return ans;
}

TEST(GetMinimumDifferenceTest, SampleTest)
{
    TreeNode five {5};
    TreeNode nine {9};

    const TreeNode one {1};
    const TreeNode seven {7};
    const TreeNode fifteen {15};

    nine.left  = &five;
    nine.right = &fifteen;

    five.left  = &one;
    five.right = &seven;

    EXPECT_EQ(2, getMinimumDifferenceRecursive(&nine));
}