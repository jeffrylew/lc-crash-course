#include <treenode.hpp>

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

//! @brief Recursive helper function to determine if tree rooted at node is BST
//! @param[in] node Pointer to current node
//! @param[in] small Lower bound (exclusive) for node's value
//! @param[in] large Upper bound (exclusive) for node's value
//! @return True if tree rooted at node is a BST, else false
static bool dfs(TreeNode* node, std::int64_t small, std::int64_t large)
{
    if (node == nullptr)
    {
        return true;
    }

    if (small >= node-> val || node->val >= large)
    {
        return false;
    }

    const bool left {
        dfs(node->left, small, static_cast<std::int64_t>(node->val))};
    const bool right {
        dfs(node->right, static_cast<std::int64_t>(node->val), large)};
    
    return left && right;
}

//! @brief Validate if binary tree is a valid BST
//! @param[in] root Pointer to root of binary tree
//! @return True if binary tree is a valid BST, else false
static bool isValidBSTRecursive(TreeNode* root)
{
    return dfs(root,
               std::numeric_limits<std::int64_t>::min(), std::numeric_limits<std::int64_t>::max());
}

TEST(IsValidBSTTest, SampleTest)
{
    TreeNode five {5};
    TreeNode ten {10};
    TreeNode twelve {12};

    const TreeNode two {2};
    const TreeNode eight {8};
    const TreeNode twenty_three {23};

    ten.left  = &five;
    ten.right = &twelve;

    five.left  = &two;
    five.right = &eight;

    twelve.right = &twenty_three;

    EXPECT_TRUE(isValidBSTRecursive(&ten));
}