#include "treenode.hpp"

#include <gtest/gtest.h>

#include <queue>
#include <vector>

//! @brief Get values of nodes you can see on right side of binary tree
//! @param[in] root Pointer to root of binary tree
//! @return Right side nodes of binary tree ordered from top to bottom
static std::vector<int> rightSideView(TreeNode* root)
{
    if (root == nullptr)
    {
        return {};
    }

    std::vector<int>      ans {};
    std::queue<TreeNode*> queue {};
    queue.push(root);

    while (not queue.empty())
    {
        const auto currentLength = static_cast<int>(queue.size());
        ans.push_back(queue.back()->val);

        for (int i = 0; i < currentLength; ++i)
        {
            const auto node = queue.front();
            queue.pop();

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

    return ans;

} // static std::vector<int> rightSideView( ...

TEST(RightSideViewTest, SampleTest)
{
    TreeNode one {1};
    TreeNode three {3};

    const TreeNode two {2};
    const TreeNode four {4};
    const TreeNode five {5};

    one.left  = &two;
    one.right = &three;

    three.left  = &four;
    three.right = &five;

    const std::vector<int> expected_output {1, 3, 5};
    EXPECT_EQ(expected_output, rightSideView(&one));
}