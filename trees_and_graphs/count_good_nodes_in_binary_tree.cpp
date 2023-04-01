#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <limits>

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