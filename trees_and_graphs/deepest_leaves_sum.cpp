#include "treenode.hpp"

#include <gtest/gtest.h>

#include <queue>

//! @brief First attempt solution to get sum of values of deepest leaves
//! @param[in] root Pointer to root of binary tree
//! @return Sum of values of deepest leaves
static int deepestLeavesSumFA(TreeNode* root)
{
    int sum {};

    std::queue<TreeNode*> queue {};
    queue.push(root);

    while (not queue.empty())
    {
        const auto currentLevel = static_cast<int>(queue.size());
        sum = 0;

        for (int i = 0; i < currentLevel; ++i)
        {
            const auto node = queue.front();
            queue.pop();

            sum += node->val;

            if (node->left != nullptr)
            {
                queue.push(node->left);
            }

            if (node->right != nullptr)
            {
                queue.push(node->right);
            }
        }
    }

    return sum;

} // static int deepestLeavesSumFA( ...

TEST(DeepestLeavesSumTest, SampleTest)
{
    TreeNode one {1};
    TreeNode two {2};
    TreeNode three {3};
    TreeNode four {4};
    TreeNode six {6};

    const TreeNode five {5};
    const TreeNode seven {7};
    const TreeNode eight {8};

    one.left  = &two;
    one.right = &three;

    two.left  = &four;
    two.right = &five;

    four.left = &seven;

    three.right = &six;

    six.right = &eight;

    EXPECT_EQ(15, deepestLeavesSumFA(&one));
}