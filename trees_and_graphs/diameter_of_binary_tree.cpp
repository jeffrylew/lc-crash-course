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

//! @brief Recursive helper function to get longest path from node to leaf
//! @param[in]  node     Current node in binary tree
//! @param[out] diameter Tracks longest path updated with sum of left and right
//! @reurn Length of longest branch between a node's left and right branches
static int longestPath(TreeNode* node, int& diameter)
{
    if (node == nullptr)
    {
        return 0;
    }

    //! Recursively find the longest path in both left child and right child
    const int leftPath = longestPath(node->left, diameter);
    const int rightPath = longestPath(node->right, diameter);

    //! Update the diameter if leftPath + rightPath is larger
    //! diameter keeps track of longest path at each node with sum of node's
    //! left and right branches
    diameter = std::max(diameter, leftPath + rightPath);

    //! Return the longer between leftPath and rightPath
    //! Remember to add 1 for the path connecting the node and its parent
    return std::max(leftPath, rightPath) + 1;
}

//! @brief Get length of diameter of the tree
//! @param[in] root Pointer to root of binary tree
//! @return Length of longest path between any two nodes in a tree
static int diameterOfBinaryTreeDS(TreeNode* root)
{
    //! @details https://leetcode.com/problems/diameter-of-binary-tree/
    //!          editorial/
    //!
    //!          Time complexity O(N) where N is number of nodes in tree.
    //!          In longestPath, only enter and exit from each node once - each
    //!          node is entered from its parent, and in a tree, nodes only have
    //!          one parent.
    //!          Space complexity O(N). Depends on size of call stack during DFS
    //!          which relates to height of tree. In worst case, tree is skewed
    //!          so height is O(N). If tree is balanced it'd be O(log N)

    int diameter {};
    longestPath(root, diameter);
    return diameter;
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

    EXPECT_EQ(3, diameterOfBinaryTreeDS(&one));
}