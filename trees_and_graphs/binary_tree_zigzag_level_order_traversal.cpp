#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <queue>
#include <vector>

//! @brief Helper function to add node's left child before right to queue
//! @param[in]  node  Pointer to current TreeNode
//! @param[out] queue Reference to queue of pointers to TreeNode
//! @pre node is not nullptr
static void add_left_first(TreeNode* node, std::queue<TreeNode*>& queue)
{
    if (node->left != nullptr)
    {
        queue.push(node->left);
    }

    if (node->right != nullptr)
    {
        queue.push(node->right);
    }
}

//! @brief Helper function to add node's right child before left to queue
//! @param[in]  node  Pointer to current TreeNode
//! @param[out] queue Reference to queue of pointers to TreeNode
//! @pre node is not nullptr
static void add_right_first(TreeNode* node, std::queue<TreeNode*>& queue)
{
    if (node->right != nullptr)
    {
        queue.push(node->right);
    }

    if (node->left != nullptr)
    {
        queue.push(node->left);
    }
}

//! @brief First attempt to get zigzag level order traversal of nodes' values
//! @param[in] root Pointer to root of binary tree
//! @return Zigzag level order traversal of node values
static std::vector<std::vector<int>> zigzagLevelOrderFA(TreeNode* root)
{
    if (root == nullptr)
    {
        return {};
    }

    std::vector<std::vector<int>> zigzag {};
    std::queue<TreeNode*>         queue {};
    queue.push(root);

    //! Switch for adding right child before left child if true
    bool right_to_left {true};

    while (not queue.empty())
    {
        const auto currentLevel = static_cast<int>(queue.size());
        zigzag.push_back({});

        for (int i = 0; i < currentLevel; ++i)
        {
            const auto node = queue.front();
            queue.pop();

            zigzag.back().push_back(node->val);

            right_to_left
                ? add_right_first(node, queue)
                : add_left_first(node, queue);
        }

        //! Now flip right_to_left
        right_to_left = not right_to_left;
    }

    return zigzag;

} // static std::vector<std::vector<int>> zigzagLevelOrderFA( ...

TEST(ZigzagLevelOrderTest, SampleTest)
{
    TreeNode three {3};
    TreeNode twenty {20};

    const TreeNode seven {7};
    const TreeNode nine {9};
    const TreeNode fifteen {15};

    three.left  = &nine;
    three.right = &twenty;

    twenty.left  = &fifteen;
    twenty.right = &seven;

    const std::vector<std::vector<int>> expected_output {{3}, {20, 9}, {15, 7}};
    
    const auto resultFA = zigzagLevelOrderFA(&three);
    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           resultFA.cbegin()));
}

TEST(ZigzagLevelOrderTest, VTree)
{
    TreeNode one {1};
    TreeNode two {2};
    TreeNode three {3};

    const TreeNode four {4};
    const TreeNode five {5};

    one.left  = &two;
    one.right = &three;

    two.left = &four;

    three.right = &five;

    const std::vector<std::vector<int>> expected_output {{1}, {3, 2}, {4, 5}};

    //! I realized my first attempt solution does not produce the zig-zag
    const auto resultFA = zigzagLevelOrderFA(&one);
    EXPECT_FALSE(std::equal(expected_output.cbegin(),
                            expected_output.cend(),
                            resultFA.cbegin()));
}