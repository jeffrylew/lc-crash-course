#include "treenode.hpp"

#include <gtest/gtest.h>

#include <queue>
#include <stack>
#include <utility>

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

//! @brief Get deepest leaves sum with iterative DFS Preorder Traversal
//! @param[in] root Pointer to root of binary tree
//! @return Sum of values of deepest leaves
static int deepestLeavesSumDS1(TreeNode* root)
{
    //! @details Time complexity O(N) since one has to visit each node
    //!          Space complexity up to O(H) to keep the stack, where H is tree
    //!          height

    int deepestSum {};
    int depth {};
    int currDepth {};

    std::stack<std::pair<TreeNode*, int>> stack {};
    stack.emplace(root, 0);

    while (not stack.empty())
    {
        const auto p = stack.top();
        stack.pop();

        root      = p.first;
        currDepth = p.second;

        if (root->left == nullptr && root->right == nullptr)
        {
            //! If this leaf is the deepest one seen so far
            if (depth < currDepth)
            {
                //! Start new sum
                deepestSum = root->val;

                //! Note new depth
                depth = currDepth;
            }
            else if (depth == currDepth)
            {
                //! If there were already leaves at this depth
                //! Update existing sum
                deepestSum += root->val;
            }
        }
        else
        {
            if (root->right != nullptr)
            {
                stack.emplace(root->right, currDepth + 1);
            }

            if (root->left != nullptr)
            {
                stack.emplace(root->left, currDepth + 1);
            }
        }
    }

    return deepestSum;

} // static int deepestLeavesSumDS1( ...

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
    EXPECT_EQ(15, deepestLeavesSumDS1(&one));
}