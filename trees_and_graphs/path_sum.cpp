#include "treenode.hpp"

#include <gtest/gtest.h>

#include <stack>
#include <utility>

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

//! @brief Iterative solution to determine if path exists with targetSum
//! @param[in] node      Pointer to root TreeNode
//! @param[in] targetSum Target sum of nodes from root to leaf
//! @return True if there is targetSum path starting at root and ending at leaf
static bool hasPathSumIterative(TreeNode* root, int targetSum)
{
    //! @details Time complexity O(N) where N is number of nodes in tree. Each
    //!          node is visited at most once.
    //!          Space complexity O(N), each visit involves constant work. In
    //!          the worst case scenario, the stack will grow to same size as
    //!          number of nodes in the tree that is a straight line.

    if (root == nullptr)
    {
        return false;
    }

    std::stack<std::pair<TreeNode*, int>> stack {};
    stack.emplace(root, 0);

    while (not stack.empty())
    {
        auto [node, curr] = stack.top();
        stack.pop();

        if (node->left == nullptr
            && node->right == nullptr
            && curr + node->val == targetSum)
        {
            return true;
        }

        curr += node->val;
        if (node->left != nullptr)
        {
            stack.emplace(node->left, curr);
        }

        if (node->right != nullptr)
        {
            stack.emplace(node->right, curr);
        }
    }

    return false;

} // static bool hasPathSumIterative( ...

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
    EXPECT_TRUE(hasPathSumIterative(&five, 22));
}