#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <stack>
#include <utility>

//! @brief First attempt recursive solution to find minimum depth of binary tree
//! @param[in] root Pointer to root of binary tree
//! @return Number of nodes along shortest depth from root node to leaf node
static int minDepthFARecursive(TreeNode* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    if (root->left == nullptr && root->right == nullptr)
    {
        return 1;
    }

    const int lhs_depth = minDepthFARecursive(root->left);
    const int rhs_depth = minDepthFARecursive(root->right);

    if (lhs_depth > 0 && rhs_depth > 0)
    {
        return 1 + std::min(lhs_depth, rhs_depth);
    }

    return 1 + ((lhs_depth == 0) ? rhs_depth : lhs_depth);
}

//! @brief Recursive discussion solution to find minimum depth of binary tree
//! @param[in] root Pointer to root of binary tree
//! @return Number of nodes along shortest depth from root node to leaf node
static int minDepthRecursive(TreeNode* root)
{
    //! @details https://leetcode.com/problems/minimum-depth-of-binary-tree/
    //!          editorial/
    //!
    //!          Time complexity O(N) where N is number of nodes. Visit each
    //!          node exactly once.
    //!          Space complexity O(N) in the worst case where tree is
    //!          completely unbalanced (each node has only one child node).
    //!          Recursion call would occur N times (height of tree) so storage
    //!          for call stack would be O(N). In best case of a balanced tree,
    //!          height of tree would be log(N) leading to O(log(N)).

    if (root == nullptr)
    {
        return 0;
    }

    if (root->left == nullptr && root->right == nullptr)
    {
        return 1;
    }

    int min_depth {std::numeric_limits<int>::max()};
    if (root->left != nullptr)
    {
        min_depth = std::min(minDepthRecursive(root->left), min_depth);
    }

    if (root->right != nullptr)
    {
        min_depth = std::min(minDepthRecursive(root->right), min_depth);
    }

    return min_depth + 1;
}

//! @brief First attempt iterative solution to find minimum depth of binary tree
//! @param[in] root Pointer to root of binary tree
//! @return Number of nodes along shortest depth from root node to leaf node
static int minDepthFAIterative(TreeNode* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int min_depth {std::numeric_limits<int>::max()};

    std::stack<std::pair<TreeNode*, int>> stack {};
    stack.emplace(root, 1);

    while (not stack.empty())
    {
        const auto [node, depth] = stack.top();
        stack.pop();

        if (node->left == nullptr && node->right == nullptr)
        {
            min_depth = std::min(min_depth, depth);
            continue;
        }
        
        if (node->left != nullptr)
        {
            stack.emplace(node->left, 1 + depth);
        }

        if (node->right != nullptr)
        {
            stack.emplace(node->right, 1 + depth);
        }
    }

    return min_depth;
}

//! @brief Iterative DFS discussion solution to find min depth of binary tree
//! @param[in] root Pointer to root of binary tree
//! @return Number of nodes along shortest depth from root node to leaf node
static int minDepthDFSIterative(TreeNode* root)
{
    //! @details Time complexity O(N), each node is visited exactly once
    //!          Space complexity O(N) in worst case of storing entire tree

    if (root == nullptr)
    {
        return 0;
    }

    std::stack<std::pair<TreeNode*, int>> stack {};
    stack.emplace(root, 1);

    int min_depth {std::numeric_limits<int>::max()};
    while (not stack.empty())
    {
        const auto [node, current_depth] = stack.top();
        stack.pop();

        if (node->left == nullptr && node->right == nullptr)
        {
            min_depth = std::min(min_depth, current_depth);
        }

        if (node->left != nullptr)
        {
            stack.emplace(node->left, current_depth + 1);
        }

        if (node->right != nullptr)
        {
            stack.emplace(node->right, current_depth + 1);
        }
    }

    return min_depth;
}

TEST(MinDepthTest, SampleTest)
{
    TreeNode three {3};
    TreeNode twenty {20};

    const TreeNode seven {7};
    const TreeNode nine {9};
    const TreeNode fifteen {15};

    three.left  = &nine;
    three.right = &twenty;

    twenty.left  = &fifteen;
    twenty.right = &seven;

    EXPECT_EQ(2, minDepthFARecursive(&three));
    EXPECT_EQ(2, minDepthRecursive(&three));
    EXPECT_EQ(2, minDepthFAIterative(&three));
    EXPECT_EQ(2, minDepthDFSIterative(&three));
}

TEST(MinDepthTest, LinearTreeTest)
{
    TreeNode two {2};
    TreeNode three {3};
    TreeNode four {4};
    TreeNode five {5};

    const TreeNode six {6};

    two.right   = &three;
    three.right = &four;
    four.right  = &five;
    five.right  = &six;

    EXPECT_EQ(5, minDepthFARecursive(&two));
    EXPECT_EQ(5, minDepthRecursive(&two));
    EXPECT_EQ(5, minDepthFAIterative(&two));
    EXPECT_EQ(5, minDepthDFSIterative(&two));
}