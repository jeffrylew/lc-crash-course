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

//! @brief First attempt iterative solution to find minimum depth of binary tree
//! @param[in] root Pointer to root of binary tree
//! @return Number of nodes along shortest depth from root node to leaf node
static int minDepthIterative(TreeNode* root)
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
    EXPECT_EQ(2, minDepthFAIterative(&three));
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
    EXPECT_EQ(5, minDepthFAIterative(&two));
}