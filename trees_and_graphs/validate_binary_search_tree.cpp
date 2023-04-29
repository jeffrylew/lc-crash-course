#include <treenode.hpp>

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <stack>

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

//! @brief Recursive solution to validate if binary tree is a valid BST
//! @param[in] root Pointer to root of binary tree
//! @return True if binary tree is a valid BST, else false
static bool isValidBSTRecursive(TreeNode* root)
{
    return dfs(root,
               std::numeric_limits<std::int64_t>::min(), std::numeric_limits<std::int64_t>::max());
}

//! @struct Bound
//! @brief Stores node and the lower and upper bounds (exclusive) for its value
struct Bound
{
    TreeNode*    node {nullptr};
    std::int64_t small {};
    std::int64_t large {};

    Bound()  = default;
    ~Bound() = default;

    Bound(TreeNode* node_in, std::int64_t small_in, std::int64_t large_in)
        : node {node_in}
        , small {small_in}
        , large {large_in}
    {
    }
};

//! @brief Iterative solution to validate if binary tree is a valid BST
//! @param[in] root Pointer to root of binary tree
//! @return True if binary tree is a valid BST, else false
static bool isValidBSTIterative(TreeNode* root)
{
    //! Alternatively could use std::tuple
    std::stack<Bound> stack {};
    stack.emplace(root,
                  std::numeric_limits<std::int64_t>::min(),
                  std::numeric_limits<std::int64_t>::max());
    
    while (not stack.empty())
    {
        const auto b = stack.top();
        stack.pop();

        if (b.small >= b.node->val || b.node->val >= b.large)
        {
            return false;
        }

        if (b.node->left != nullptr)
        {
            stack.emplace(b.node->left, b.small, b.node->val);
        }

        if (b.node->right != nullptr)
        {
            stack.emplace(b.node->right, b.node->val, b.large);
        }
    }

    return true;
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
    EXPECT_TRUE(isValidBSTIterative(&ten));
}