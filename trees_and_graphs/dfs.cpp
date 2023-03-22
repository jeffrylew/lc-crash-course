#include "treenode.cpp"

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