#include "treenode.hpp"

#include <gtest/gtest.h>

static void dfs(TreeNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    dfs(node->left);
    dfs(node->right);
}

TEST(DFS_Test, SampleTest)
{
    TreeNode root {1};
    EXPECT_EQ(1, root.val);

    dfs(&root);
}