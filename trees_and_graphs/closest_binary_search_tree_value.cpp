#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <stack>
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

//! @brief Iterative solution to get smallest value in BST closest to target
//! @param[in] root   Pointer to root of binary search tree
//! @param[in] target Target value to get value in BST that is closest
//! @return Value in BST closest to target. If have multiple, print smallest
static int closestValueIterative(TreeNode* root, double target)
{
    //! @details https://leetcode.com/problems/closest-binary-search-tree-value/
    //!          editorial/
    //!
    //!          Optimize recursive solution in case when index k of closest
    //!          node is much smaller than the tree height H.
    //!
    //!          Time complexity O(k) in the average case and O(H + k) in the
    //!          worst case where k is the index of the closest element and
    //!          H = O(log N). The average case is a balanced tree - one does 2k
    //!          operations to go to kth element in inorder traversal (k times
    //!          to push into stack and then k times to pop out of stack)
    //!          resulting in O(k) time complexity. Worst case is completely
    //!          unbalanced tree - first push H elements into stack then pop out
    //           k elements, resulting in O(H + k) time complexity.
    //!          Space complexity O(H) to keep stack for non-balanced tree

    auto node = root;

    std::stack<TreeNode*> stack {};

    //! Initialize predecessor value as a small number
    //! Don't use numeric_limits<double>::lowest() since we subtract from it
    auto pred = static_cast<double>(std::numeric_limits<std::int64_t>::min());

    while (not stack.empty() || node != nullptr)
    {
        //! Go left as far as you can and add all nodes to stack
        while (node != nullptr)
        {
            stack.push(node);
            node = node->left;
        }

        //! node is nullptr so set to top of stack
        node = stack.top();
        stack.pop();

        const auto node_val = static_cast<double>(node->val);

        //! If target is in-between pred and node_val, return closest node val
        if (pred <= target && target < node_val)
        {
            // Need to use <= instead of < to get smallest value that is closest
            // to the target. e.g. target = 3.5, BST contains 3 and 4, return 3
            return std::abs(pred - target) <= std::abs(node_val - target)
                ? static_cast<int>(pred) : node->val;
        }

        pred = node_val;
        node = node->right;
    }

    //! Could not identify closest value during loop. This means closest value
    //! is last value in inorder traversal, i.e. current predecessor value
    return static_cast<int>(pred);

} // static int closestValueIterative( ...

//! @brief Binary search solution to get smallest value in BST closest to target
//! @param[in] root   Pointer to root of binary search tree
//! @param[in] target Target value to get value in BST that is closest
//! @return Value in BST closest to target. If have multiple, print smallest
static int closestValueBinarySearch(TreeNode* root, double target)
{
    //! @details https://leetcode.com/problems/closest-binary-search-tree-value/
    //!          editorial/
    //!
    //!          Iterative solution above is fine when index k of closest
    //!          element is much smaller than the tree height H. In the limit of
    //!          relatively large k comparable with N, use binary search.
    //!
    //!          Time complexity O(H) since one goes from root down to leaf
    //!          Space complexity O(1)

    //! Editorial assumes root is not nullptr here
    auto node = root;
    int  val {node->val};
    int  closest {node->val};

    while (node != nullptr)
    {
        val = node->val;

        /*
         * Editorial solution does not pass all cases, see modification below
         *
        closest = std::abs(static_cast<double>(val) - target)
            <= std::abs(static_cast<double>(closest) - target) ? val : closest;
         */

        const auto val_diff   = std::abs(static_cast<double>(val) - target);
        const auto close_diff = std::abs(static_cast<double>(closest) - target);

        if (val_diff < close_diff)
        {
            closest = val;
        }
        else if (val_diff == close_diff)
        {
            closest = std::min(val, closest);
        }

        node = target < static_cast<double>(val) ? node->left : node->right;
    }

    return closest;

} // static int closestValueBinarySearch( ...

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
    EXPECT_EQ(4, closestValueIterative(&four, 3.714286));
    EXPECT_EQ(4, closestValueBinarySearch(&four, 3.714286));
}

TEST(ClosestValueTest, OneTwoTest)
{
    TreeNode       one {1};
    const TreeNode two {2};

    one.right = &two;

    EXPECT_EQ(2, closestValueFA(&one, 3.428571));
    EXPECT_EQ(2, closestValueRecursive(&one, 3.428571));
    EXPECT_EQ(2, closestValueIterative(&one, 3.428571));
    EXPECT_EQ(2, closestValueBinarySearch(&one, 3.428571));
}