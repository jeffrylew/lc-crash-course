#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

//! @brief First attempt solution to get smallest value in BST closest to target
//! @param[in] root   Pointer to root of binary search tree
//! @param[in] target Target value to get value in BST that is closest
//! @return Value in BST closest to target. If have multiple, print smallest
static int closestValueFA(TreeNode* root, double target)
{
    if (root == nullptr)
    {
        return 0;
    }

    TreeNode* node = root;
    double    min_diff {std::numeric_limits<double>::max()};
    int       closest_val {root->val};

    while (node != nullptr)
    {
        const auto   node_val = static_cast<double>(node->val);
        const double curr_diff {std::abs(node_val - target)};

        if (min_diff > curr_diff)
        {
            //! Current node is closer than any previous node
            //! Update min_diff and closest_val
            min_diff    = curr_diff;
            closest_val = node->val;
        }
        else if (min_diff == curr_diff)
        {
            //! If difference between current node val and target matches the
            //! current minimum difference then check if node's value is smaller
            //! than the current closest node and update accordingly
            if (node->val < closest_val)
            {
                closest_val = node->val;
            }
        }

        if (target < node_val)
        {
            if (node->left != nullptr)
            {
                node = node->left;
            }
            else
            {
                return closest_val;
            }
        }
        else
        {
            if (node->right != nullptr)
            {
                node = node->right;
            }
            else
            {
                return closest_val;
            }
        }
    }

    return closest_val;

} // static int closestValueFA( ...

//! @brief Recursively build inorder traversal vector
//! @param[in]  node Pointer to current node in binary search tree
//! @param[out] nums Reference to vector of sorted node values
static void inorder(TreeNode* node, std::vector<int>& nums)
{
    if (node == nullptr)
    {
        return;
    }

    inorder(node->left, nums);
    nums.push_back(node->val);
    inorder(node->right, nums);
}

//! @brief Recursive solution to get smallest value in BST closest to target
//! @param[in] root   Pointer to root of binary search tree
//! @param[in] target Target value to get value in BST that is closest
//! @return Value in BST closest to target. If have multiple, print smallest
static int closestValueRecursive(TreeNode* root, double target)
{
    //! @details https://leetcode.com/problems/closest-binary-search-tree-value/
    //!          editorial/
    //!
    //!          Build inorder traversal and then find closest element in sorted
    //!          vector.
    //!
    //!          Time complexity O(N) where N = number of nodes in BST. Linear
    //!          time to build inorder traversal and perform linear search.
    //!          Space complexity O(N) to keep inorder traversal.

    std::vector<int> nums {};
    inorder(root, nums);
    return *std::min_element(nums.cbegin(),
                             nums.cend(),
                             [tgt = target](int lhs, int rhs) -> bool {
                                 const auto l = static_cast<double>(lhs);
                                 const auto r = static_cast<double>(rhs);
                                 return std::abs(l - tgt) < std::abs(r - tgt);
                             });

} // static int closestValueRecursive( ...

TEST(ClosestValueTest, SampleTest)
{
    TreeNode two {2};
    TreeNode four {4};

    const TreeNode one {1};
    const TreeNode three {3};
    const TreeNode five {5};

    four.left  = &two;
    four.right = &five;

    two.left  = &one;
    two.right = &three;

    EXPECT_EQ(4, closestValueFA(&four, 3.714286));
    EXPECT_EQ(4, closestValueRecursive(&four, 3.714286));
}

TEST(ClosestValueTest, OneTwoTest)
{
    TreeNode       one {1};
    const TreeNode two {2};

    one.right = &two;

    EXPECT_EQ(2, closestValueFA(&one, 3.428571));
    EXPECT_EQ(2, closestValueRecursive(&one, 3.428571));
}