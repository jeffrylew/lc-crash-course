#include "treenode.hpp"

#include <gtest/gtest.h>

#include <vector>

static void postorderDfs(TreeNode* node, std::vector<int>& vals)
{
    if (node == nullptr)
    {
        return;
    }

    postorderDfs(node->left, vals);
    postorderDfs(node->right, vals);
    val.push_back(node->val);
}

TEST(PostorderDfsTest, SampleTest)
{
    TreeNode zero {0};
    TreeNode one {1};
    TreeNode two {2};
    TreeNode four {4};

    const TreeNode three {3};
    const TreeNode five {5};
    const TreeNode six {6};

    zero.left  = &one;
    zero.right = &two;

    one.left  = &three;
    one.right = &four;

    two.right  = &five;
    four.right = &six;

    const std::vector<int> expected_output {3, 6, 4, 1, 5, 2, 0};
    
    std::vector<int> result;
    result.reserve(expected_output.size());

    postorderDfs(&zero, result);
    EXPECT_EQ(expected_output, result);
}