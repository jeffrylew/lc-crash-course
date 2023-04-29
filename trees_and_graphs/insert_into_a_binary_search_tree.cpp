#include "treenode.hpp"

#include <gtest/gtest.h>

#include <stack>

//! @brief First attempt solution to insert val into BST
//! @param[in] root Pointer to root of binary search tree
//! @param[in] val  Value to insert into the tree
//! @return Root node of BST after insertion
static TreeNode* insertIntoBSTFA(TreeNode* root, int val)
{
    // In LC, should use
    //     TreeNode* node_to_add = new TreeNode(val);
    //     node->left = node_to_add;
    //     node->right = node_to_add;
    // since their test program uses malloc and frees the memory after
    static TreeNode node_to_add {val};
    if (root == nullptr)
    {
        return &node_to_add;
    }

    auto root_node = root;

    std::stack<TreeNode*> stack {};
    stack.push(root_node);

    while (not stack.empty())
    {
        auto node = stack.top();
        stack.pop();

        if (val < node->val)
        {
            if (node->left == nullptr)
            {
                node->left = &node_to_add;
                return root;
            }
            else
            {
                stack.push(node->left);
                continue;
            }
        }
        else if (val > node->val)
        {
            if (node->right == nullptr)
            {
                node->right = &node_to_add;
                return root;
            }
            else
            {
                stack.push(node->right);
                continue;
            }
        }
    }

    return root;

} // static TreeNode* insertIntoBSTFA( ...

TEST(InsertIntoBSTTest, SampleTest)
{
    TreeNode two {2};
    TreeNode four {4};
    TreeNode seven {7};

    const TreeNode one {1};
    const TreeNode three {3};

    four.left  = &two;
    four.right = &seven;

    two.left  = &one;
    two.right = &three;

    const auto root = insertIntoBSTFA(&four, 5);
    EXPECT_EQ(5, seven.left->val);
}