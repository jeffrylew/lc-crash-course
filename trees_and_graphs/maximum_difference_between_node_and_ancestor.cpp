#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>

//! @brief Update max difference using max and min values from root to node
//! @param[in]  node     Pointer to current TreeNode
//! @param[out] max_diff Maximum difference for ancestors between root and node
//! @param[in]  curMax   Current maximum value along path from root to node
//! @param[in]  curMin   Current minimum value along path from root to node
static void helper1(TreeNode* node, int& max_diff, int curMax, int curMin)
{
    if (node == nullptr)
    {
        return;
    }

    //! Update max_diff
    const int possible_max_diff {std::max(std::abs(curMax - node->val),
                                          std::abs(curMin - node->val))};
    max_diff = std::max(max_diff, possible_max_diff);

    //! Update the max and min
    curMax = std::max(curMax, node->val);
    curMin = std::min(curMin, node->val);

    helper1(node->left, max_diff, curMax, curMin);
    helper1(node->right, max_diff, curMax, curMin);

} // static void helper1( ...

//! @brief First recursive solution to get max |a.val - b.val|
//! @param[in] root Pointer to root of binary tree
//! @return Max value |a.val - b.val| where a is an ancestor of b
static int maxAncestorDiffRecursive1(TreeNode* root)
{
    //! @details https://leetcode.com/problems/
    //!          maximum-difference-between-node-and-ancestor/editorial/
    //!
    //!          Time complexity O(N) where N = number of nodes in binary tree.
    //!          We visit all nodes once.
    //!          Space complexity O(N) since max depth of recursion is height of
    //!          tree, which is O(N) in worst case and O(log(N)) in best case.

    if (root == nullptr)
    {
        return 0;
    }

    //! Record required maximum difference
    int result {};
    helper1(root, result, root->val, root->val);
    return result;
}

//! @brief Record max and min of all root-to-leav paths and return max diff
//! @param[in] node   Pointer to current TreeNode
//! @param[in] curMax Current maximum value along path from root to node
//! @param[in] curMin Current minimum value along path from root to node
//! @return cur_max - cur_min when encountering leaves
static int helper2(TreeNode* node, int curMax, int curMin)
{
    //! If encounter a leaf, return max - min along the path
    if (node == nullptr)
    {
        return curMax - curMin;
    }

    //! Else update max and min and return max of left and right subtrees
    curMax = std::max(curMax, node->val);
    curMin = std::min(curMin, node->val);

    const int left {helper(node->left, curMax, curMin)};
    const int right {helper(node->right, curMax, curMin)};

    return std::max(left, right);

} // static int helper2( ...

//! @brief Second recursive solution to get max |a.val - b.val|
//! @param[in] root Pointer to root of binary tree
//! @return Max value |a.val - b.val| where a is an ancestor of b
static int maxAncestorDiffRecursive2(TreeNode* root)
{
    //! @details https://leetcode.com/problems/
    //!          maximum-difference-between-node-and-ancestor/editorial/
    //!
    //!          Time complexity O(N) where N = number of nodes in binary tree.
    //!          We visit all nodes once.
    //!          Space complexity O(N) since max depth of recursion is height of
    //!          tree, which is O(N) in worst case and O(log(N)) in best case.

    if (root == nullptr)
    {
        return 0;
    }

    return helper2(root, root->val, root->val);
}

TEST(MaxAncestorDiffTest, ExampleTest1)
{
    TreeNode three {3};
    TreeNode six {6};
    TreeNode eight {8};
    TreeNode ten {10};
    TreeNode fourteen {14};

    const TreeNode one {1};
    const TreeNode four {4};
    const TreeNode seven {7};
    const TreeNode thirteen {13};

    eight.left  = &three;
    eight.right = &ten;

    three.left  = &one;
    three.right = &six;

    six.left  = &four;
    six.right = &seven;

    ten.right = &fourteen;

    fourteen.left = &thirteen;

    EXPECT_EQ(7, maxAncestorDiffRecursive1(&eight));
    EXPECT_EQ(7, maxAncestorDiffRecursive2(&eight));
}

TEST(MaxAncestorDiffTest, ExampleTest2)
{
    TreeNode       zero {0};
    TreeNode       one {1};
    TreeNode       two {2};
    const TreeNode three {3};

    one.right = &two;
    two.right = &zero;
    zero.left = &three;

    EXPECT_EQ(3, maxAncestorDiffRecursive1(&one));
    EXPECT_EQ(3, maxAncestorDiffRecursive2(&one));
}