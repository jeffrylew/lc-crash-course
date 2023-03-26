#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>

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
}