#include "treenode.hpp"

#include <gtest/gtest.h>

//! @brief Recursive helper function to determine if path exists with targetSum
//! @param[in] node      Pointer to TreeNode
//! @param[in] targetSum Target sum of nodes from root to leaf
//! @param[in] curr      Current sum of nodes from root to current node
//! @return True if there is targetSum path starting at node and ending at leaf
static bool dfs(TreeNode* node, int targetSum, int curr)
{
    if (node == nullptr)
    {
        return false;
    }

    if (node->left == nullptr && node->right == nullptr)
    {
        return (curr + node->val) == targetSum;
    }

    curr += node->val;
    const bool left  = dfs(node->left, targetSum, curr);
    const bool right = dfs(node->right, targetSum, curr);
    return left || right;
}

//! @brief Recursive solution to determine if path exists with targetSum
//! @param[in] node      Pointer to root TreeNode
//! @param[in] targetSum Target sum of nodes from root to leaf
//! @return True if there is targetSum path starting at root and ending at leaf
static bool hasPathSumRecursive(TreeNode* root, int targetSum)
{
    return dfs(root, targetSum, 0);
}

Test(HasPathSumTest, SampleTest)
{
    TreeNode four {4};
    TreeNode five {5};
    TreeNode eleven {11};

    const TreeNode two {2};
    const TreeNode seven {7};

    five.left    = &four;
    four.left    = &eleven;
    eleven.left  = &seven;
    eleven.right = &two;

    EXPECT_TRUE(hasPathSumRecursive(&five, 22));
}