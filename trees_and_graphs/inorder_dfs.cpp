#include "treenode.hpp"

#include <gtest/gtest.h>

#include <vector>

static void inorderDfs(TreeNode* node, std::vector<int>& vals)
{
    if (node == nullptr)
    {
        return;
    }

    inorderDfs(node->left, vals);
    val.push_back(node->val);
    inorderDfs(node->right, vals);
}

TEST(InorderDfsTest, SampleTest)
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

    const std::vector<int> expected_output {3, 1, 4, 6, 0, 2, 5};
    
    std::vector<int> result;
    result.reserve(expected_output.size());

    inorderDfs(&zero, result);
    EXPECT_EQ(expected_output, result);
}