#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <stack>
#include <utility>

//! @brief Recursive solution to find length of longest path from root to leaf
//! @param[in] root Pointer to root of binary tree
//! @return Length of longest path from root to leaf
static int maxDepthRecursive(TreeNode* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    const int left = maxDepthRecursive(root->left);
    const int right = maxDepthRecursive(root->right);

    //! Usually depth of root is 0 but for this problem it is 1
    //! (number of nodes on path from root to leaf, need to include root)
    return std::max(left, right) + 1;
}

//! @brief Iterative solution to find length of longest path from root to leaf
//! @param[in] root Pointer to root of binary tree
//! @return Length of longest path from root to leaf
static int maxDepthIterative(TreeNode* root)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /707/traversals-trees-graphs/4686/
    //!
    //!          Time complexity O(N) where N = total number of nodes. Each node
    //!          is visited once and at each node, O(1) work is done.
    //!          Space complexity O(N) in worst case if tree is a straight line.
    //!          O(log N) for a complete tree (all nodes have 0 or 2 children
    //!          and each level except the last is full).

    if (root == nullptr)
    {
        return 0;
    }

    std::stack<std::pair<TreeNode*, int>> stack {};
    stack.emplace(root, 1);

    int ans {};

    while (not stack.empty())
    {
        auto [node, depth] = stack.top();
        stack.pop();

        ans = std::max(ans, depth);

        if (node->left != nullptr)
        {
            stack.emplace(node->left, depth + 1);
        }

        if (node->right != nullptr)
        {
            stack.emplace(node->right, depth + 1);
        }
    }

    return ans;

} // static int maxDepthIterative( ...

TEST(MaxDepthTest, SampleTest)
{
    TreeNode zero {0};
    TreeNode one {1};
    TreeNode two {2};
    TreeNode five {5};

    const TreeNode three {3};
    const TreeNode four {4};
    const TreeNode six {6};

    zero.left  = &one;
    zero.right = &two;

    one.left  = &three;
    one.right = &four;

    two.right  = &five;
    five.right = &six;

    EXPECT_EQ(4, maxDepthRecursive(&zero));
    EXPECT_EQ(4, maxDepthIterative(&zero));
}

TEST(MaxDepthTest, TestCase1)
{
    TreeNode three {3};
    TreeNode twenty {20};

    const TreeNode nine {9};
    const TreeNode fifteen {15};
    const TreeNode seven {7};

    three.left  = &nine;
    three.right = &twenty;

    twenty.left  = &fifteen;
    twenty.right = &seven;

    EXPECT_EQ(3, maxDepthRecursive(&three));
    EXPECT_EQ(3, maxDepthIterative(&three));
}