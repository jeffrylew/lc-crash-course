#include "treenode.hpp"

#include <gtest/gtest.h>

#include <queue>

static std::vector<int> printAllNodes(TreeNode* root)
{
    std::vector<int>      output {};
    std::queue<TreeNode*> queue {};
    queue.push(root);

    while (not queue.empty())
    {
        const auto nodesInCurrentLevel = static_cast<int>(queue.size());

        // Do some logic here for the current level

        for (int i = 0; i < nodesInCurrentLevel; ++i)
        {
            auto node = queue.front();
            queue.pop();

            //! Do some logic on current node
            output.push_back(node->val);

            //! Put the next level onto the queue
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

    return output;

} // static std::vector<int> printAllNodes( ...

TEST(PrintAllNodesTest, SampleTest)
{
    const TreeNode one {1};
    const TreeNode two {2};
    const TreeNode seven {7};
    const TreeNode thirteen {13};

    TreeNode four_lhs {4};
    TreeNode four_rhs {4};
    TreeNode five {5};
    TreeNode eight {8};
    TreeNode eleven {11};

    five.left  = &four_lhs;
    five.right = &eight;

    four_lhs.left = &eleven;

    eleven.left  = &seven;
    eleven.right = &two;

    eight.left  = &thirteen;
    eight.right = &four_rhs;

    four.right = &one;

    const std::vector<int> expected_output {5, 4, 8, 11, 13, 4, 7, 2, 1};
    EXPECT_EQ(expected_output, printAllNodes(&five));
}

