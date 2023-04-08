#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>

//! @brief Recursive helper function to get diameter of tree
//! @param[in] node     Pointer to node in binary tree
//! @param[in] curr_dia Current diameter of tree
//! @return Diameter of tree
static int helperFARecursive(TreeNode* node, int curr_dia)
{
    if (node == nullptr)
    {
        return 0;
    }

    if (node->left == nullptr && node->right == nullptr)
    {
        return curr_dia;
    }

    const int left_len {helperFARecursive(node->left, curr_dia + 1)};
    const int right_len {helperFARecursive(node->right, curr_dia + 1)};

    return std::max(curr_dia, left_len + right_len);

} // static void helperFARecursive( ...

//! @brief Get length of diameter of the tree
//! @param[in] root Pointer to root of binary tree
//! @return Length of longest path between any two nodes in a tree
static int diameterOfBinaryTreeFARecursive(TreeNode* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return helperFARecursive(root, 0);
}

TEST(DiameterOfBinaryTreeTest, SampleTest)
{
    TreeNode one {1};
    TreeNode two {2};

    const TreeNode three {3};
    const TreeNode four {4};
    const TreeNode five {5};

    one.left  = &two;
    one.right = &three;

    two.left  = &four;
    two.right = &five;

    //! First attempt solution is not correct
    EXPECT_NE(3, diameterOfBinaryTreeFARecursive(&one));
    EXPECT_EQ(5, diameterOfBinaryTreeFARecursive(&one));
}