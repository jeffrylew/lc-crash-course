#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <vector>
#include <queue>

//! @brief Find largest value in each row of the tree
//! @param[in] root Pointer to root of binary tree
//! @return Vector of the largest value in each row of the tree
static std::vector<int> largestValues(TreeNode* root)
{
    if (root == nullptr)
    {
        return {};
    }

    std::vector<int> ans {};
    std::queue<TreeNode*> queue {};
    queue.push(root);

    while (not queue.empty())
    {
        const auto currentLength = static_cast<int>(queue.size());
        int        currMax {std::numeric_limits<int>::min()};

        for (int i = 0; i < currentLength; ++i)
        {
            const auto node = queue.front();
            currMax         = std::max(currMax, node->val);
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

        ans.push_back(currMax);
    }

    return ans;

} // static std::vector<int> largestValues( ...

TEST(LargestValuesTest, SampleTest)
{
    TreeNode one {1};
    TreeNode two {2};
    TreeNode three_up {3};
    
    const TreeNode three_down {3};
    const TreeNode five {5};
    const TreeNode nine {9};

    one.left  = &three_up;
    one.right = &two;

    three_up.left  = &five;
    three_up.right = &three_down;

    two.right = &nine;

    const std::vector<int> expected_output {1, 3, 9};
    EXPECT_EQ(expected_output, largestValues(&one));
}