#include "treenode.hpp"

#include <gtest/gtest.h>

//! @brief Get sum of nodes with a value in range [low, high]
//! @param[in] root Pointer to root of binary search tree
//! @param[in] low  Lower bound of range (inclusive)
//! @param[in] high Upper bound of range (inclusive)
//! @return Sum of all nodes with a value in [low, high]
static int rangeSumBST(TreeNode* root, int low, int high)
{
    if (root == nullptr)
    {
        return 0;
    }

    int ans {};
    if (low <= root->val && root->val <= high)
    {
        ans += root->val;
    }

    if (low < root->val)
    {
        ans += rangeSumBST(root->left, low, high);
    }

    if (root->val < high)
    {
        ans += rangeSumBST(root->right, low, high);
    }

    return ans;

} // static int rangeSumBST( ...

TEST(RangeSumBSTTest, SampleTest)
{
    TreeNode five {5};
    TreeNode ten {10};
    TreeNode fifteen {15};

    const TreeNode three {3};
    const TreeNode seven {7};
    const TreeNode eighteen {18};

    ten.left  = &five;
    ten.right = &fifteen;

    five.left  = &three;
    five.right = &seven;

    fifteen.right = &eighteen;

    EXPECT_EQ(32, rangeSumBST(&ten, 7, 15));
}