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

//! @brief Recursive solution to insert val into BST
//! @param[in] root Pointer to root of binary search tree
//! @param[in] val  Value to insert into the tree
//! @return Root node of BST after insertion
static TreeNode* insertIntoBSTRecursive(TreeNode* root, int val)
{
    //! @details https://leetcode.com/problems/insert-into-a-binary-search-tree/
    //!          editorial/
    //!
    //!          Time complexity O(H = log N) in the average case where H is the
    //!          tree height. Computed using the master theorem. O(N) in the
    //!          worst case.
    //!          Space complexity O(H = log N) to keep the recursion stack in
    //!          the average case. O(N) in the worst case.

    if (root == nullptr)
    {
        return new TreeNode(val);
    }

    if (val > root->val)
    {
        //! Insert into the right subtree
        root->right = insertIntoBSTRecursive(root->right, val);
    }
    else
    {
        //! Insert into the left subtree
        root->left = insertIntoBSTRecursive(root->left, val);
    }

    return root;

} // static TreeNode* insertIntoBSTRecursive( ...

//! @brief Iterative solution to insert val into BST
//! @param[in] root Pointer to root of binary search tree
//! @param[in] val  Value to insert into the tree
//! @return Root node of BST after insertion
static TreeNode* insertIntoBSTIterative(TreeNode* root, int val)
{
    //! @details https://leetcode.com/problems/insert-into-a-binary-search-tree/
    //!          editorial/
    //!
    //!          Time complexity O(H = log N) in the average case where H is the
    //!          tree height. Computed using the master theorem. O(N) in the
    //!          worst case.
    //!          Space complexity O(1)

    auto node = root;

    while (node != nullptr)
    {
        if (val > node->val)
        {
            //! Insert into the right subtree
            if (node->right == nullptr)
            {
                node->right = new TreeNode(val);
                return root;
            }
            else
            {
                node = node->right;
            }
        }
        else
        {
            //! Insert into the left subtree
            if (node->left == nullptr)
            {
                node->left = new TreeNode(val);
                return root;
            }
            else
            {
                node = node->left;
            }
        }

    } // while (node != nullptr)

    return new TreeNode(val);

} // static TreeNode* insertIntoBSTIterative( ...

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