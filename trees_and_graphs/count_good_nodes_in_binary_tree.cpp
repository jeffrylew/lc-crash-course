#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <limits>

//! @brief Recursive solution helper function returns answer to original problem
//! @param[in] node     Pointer to current TreeNode
//! @param[in] maxSoFar Largest value between root and current node
//! @return Number of nodes that are good
static int dfs(TreeNode* node, int maxSoFar)
{
    if (node == nullptr)
    {
        return 0;
    }

    const int left  = dfs(node->left, std::max(maxSoFar, node->val));
    const int right = dfs(node->right, std::max(maxSoFar, node->val));
    int ans         = left + right;
    if (node->val >= maxSoFar)
    {
        ++ans;
    }

    return ans;
}

//! @brief Find number of good nodes (path has no nodes with greater value)
//! @param[in] root Pointer to root of binary tree
//! @return Number of nodes that are good
static int goodNodesRecursive(TreeNode* root)
{
    return dfs(root, std::numeric_limits<int>::min());
}

TEST(GoodNodesTest, SampleTest)
{
    TreeNode four_lhs {4};
    TreeNode four_rhs {4};
    TreeNode five {5};
    TreeNode eight {8};
    TreeNode eleven {11};

    const TreeNode one {1};
    const TreeNode two {2};
    const TreeNode seven {7};
    const TreeNode thirteen {13};
    
    five.left  = &four_lhs;
    five.right = &eight;
    
    four_lhs.left = &eleven;
    
    eleven.left  = &seven;
    eleven.right = &two;

    eight.left  = &thirteen;
    eight.right = &four_rhs;

    four_rhs.right = &one;

    EXPECT_EQ(4, goodNodesRecursive(&five));
}