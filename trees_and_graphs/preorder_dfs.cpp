#include "treenode.hpp"

#include <gtest/gtest.h>

#include <vector>

static void preorderDfs(TreeNode* node, std::vector<int>& vals)
{
    if (node == nullptr)
    {
        return;
    }

    val.push_back(node->val);
    preorderDfs(node->left, vals);
    preorderDfs(node->right, vals);
}

TEST(PreorderDfsTest, SampleTest)
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

    const std::vector<int> expected_output {0, 1, 3, 4, 6, 2, 5};
    
    std::vector<int> result;
    result.reserve(expected_output.size());

    preorderDfs(&zero, result);
    EXPECT_EQ(expected_output, result);
}