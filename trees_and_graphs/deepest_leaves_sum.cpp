#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

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

        const auto node = p.first;
        currDepth       = p.second;

        if (node->left == nullptr && node->right == nullptr)
        {
            //! If this leaf is the deepest one seen so far
            if (depth < currDepth)
            {
                //! Start new sum
                deepestSum = node->val;

                //! Note new depth
                depth = currDepth;
            }
            else if (depth == currDepth)
            {
                //! If there were already leaves at this depth
                //! Update existing sum
                deepestSum += node->val;
            }
        }
        else
        {
            if (node->right != nullptr)
            {
                stack.emplace(node->right, currDepth + 1);
            }

            if (node->left != nullptr)
            {
                stack.emplace(node->left, currDepth + 1);
            }
        }
    }

    return deepestSum;

} // static int deepestLeavesSumDS1( ...

//! @brief Get deepest leaves sum with iterative BFS Traversal
//! @param[in] root Pointer to root of binary tree
//! @return Sum of values of deepest leaves
static int deepestLeavesSumDS2(TreeNode* root)
{
    //! @details Time complexity O(N) since one has to visit each node
    //!          Space complexity up to O(N) to keep the queue
    //!          The last level can contain up to N/2 tree nodes for a complete
    //!          binary tree

    int deepestSum {};
    int depth {};
    int currDepth {};

    std::queue<std::pair<TreeNode*, int>> queue {};
    queue.emplace(root, 0);

    while (not queue.empty())
    {
        const auto p = queue.front();
        queue.pop();

        const auto node = p.first;
        currDepth       = p.second;

        if (node->left == nullptr && node->right == nullptr)
        {
            //! If this leaf is the deepest one seen so far
            if (depth < currDepth)
            {
                //! Start new sum
                deepestSum = node->val;

                //! Note new depth
                depth = currDepth;
            }
            else if (depth == currDepth)
            {
                //! If there were already leaves at this depth
                //! Update existing sum
                deepestSum += node->val;
            }
        }
        else
        {
            if (node->right != nullptr)
            {
                queue.emplace(node->right, currDepth + 1);
            }

            if (node->left != nullptr)
            {
                queue.emplace(node->left, currDepth + 1);
            }
        }
    }

    return deepestSum;

} // static int deepestLeavesSumDS2( ...

//! @brief Get deepest leaves sum with optimized iterative BFS Traversal
//! @param[in] root Pointer to root of binary tree
//! @return Sum of values of deepest leaves
static int deepestLeavesSumDS3(TreeNode* root)
{
    //! @details Time complexity O(N) since one has to visit each node
    //!          Space complexity up to O(N) to keep the queues
    //!          The last level can contain up to N/2 tree nodes for a complete
    //!          binary tree

    std::vector<TreeNode*> nextLevel {};
    std::vector<TreeNode*> currLevel {};
    nextLevel.push_back(root);

    while (not nextLevel.empty())
    {
        //! Prepare for the next level
        currLevel = std::move(nextLevel);
        nextLevel.clear();

        for (const auto node : currLevel)
        {
            //! Add child nodes of the current level
            //! in the queue for the next level
            if (node->left != nullptr)
            {
                nextLevel.push_back(node->left);
            }

            if (node->right != nullptr)
            {
                nextLevel.push_back(node->right);
            }
        }
    }

    return std::accumulate(currLevel.cbegin(),
                           currLevel.cend(),
                           0,
                           [](int acc, TreeNode* node) -> int {
                               return acc + node->val;
                           });

} // static int deepestLeavesSumDS3( ...

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
    EXPECT_EQ(15, deepestLeavesSumDS2(&one));
    EXPECT_EQ(15, deepestLeavesSumDS3(&one));
}