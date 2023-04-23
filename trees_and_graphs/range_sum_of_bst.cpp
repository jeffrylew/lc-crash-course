#include "treenode.hpp"

#include <gtest/gtest.h>

#include <stack>

//! @brief Get sum of nodes with a value in range [low, high]
//! @param[in] root Pointer to root of binary search tree
//! @param[in] low  Lower bound of range (inclusive)
//! @param[in] high Upper bound of range (inclusive)
//! @return Sum of all nodes with a value in [low, high]
static int rangeSumBSTRecursive(TreeNode* root, int low, int high)
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
        ans += rangeSumBSTRecursive(root->left, low, high);
    }

    if (root->val < high)
    {
        ans += rangeSumBSTRecursive(root->right, low, high);
    }

    return ans;

} // static int rangeSumBSTRecursive( ...

//! @brief Get sum of nodes with a value in range [low, high]
//! @param[in] root Pointer to root of binary search tree
//! @param[in] low  Lower bound of range (inclusive)
//! @param[in] high Upper bound of range (inclusive)
//! @return Sum of all nodes with a value in [low, high]
static int rangeSumBSTIterative(TreeNode* root, int low, int high)
{
    //! @details Time complexity O(N) where N is number of nodes in tree
    //!          Space complexity O(N)

    std::stack<TreeNode*> stack {};
    stack.push(root);
    int ans {};

    while (not stack.empty())
    {
        const auto node = stack.top();
        stack.pop();

        if (low <= node->val && node->val <= high)
        {
            ans += node->val;
        }

        if (node->left != nullptr && low < node->val)
        {
            stack.push(node->left);
        }

        if (node->right != nullptr && node->val < high)
        {
            stack.push(node->right);
        }
    }

    return ans;

} // static int rangeSumBSTIterative( ...

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

    EXPECT_EQ(32, rangeSumBSTRecursive(&ten, 7, 15));
    EXPECT_EQ(32, rangeSumBSTIterative(&ten, 7, 15));
}