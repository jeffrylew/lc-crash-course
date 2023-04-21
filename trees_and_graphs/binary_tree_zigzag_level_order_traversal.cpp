#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
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

//! @brief BFS solution to get zigzag level order traversal of nodes' values
//! @param[in] root Pointer to root of binary tree
//! @return Zigzag level order traversal of node values
static std::vector<std::vector<int>> zigzagLevelOrderBFS(TreeNode* root)
{
    //! @details https://leetcode.com/problems/
    //!          binary-tree-zigzag-level-order-traversal/editorial/
    //!
    //!          Time complexity O(N) where N is the number of nodes. We visit
    //!          each node once. The insertion operation on either end of the
    //!          deque takes a constant time.
    //!          Space complexity O(N). The main memory is node_queue used for
    //!          the loop - at any given moment it would hold the nodes that are
    //!          at most across two levels. If L is the max number of nodes that
    //!          reside on the same level then the size of node_queue is 2L at
    //!          most. For a complete/full binary tree, L is roughly N/2. So in
    //!          the worst case 2 * N/2 = N.

    if (root == nullptr)
    {
        return {};
    }

    std::vector<std::vector<int>> results {};

    //! Add the root element with a delimiter to kick off the BFS loop
    std::queue<TreeNode*> node_queue {};
    node_queue.push(root);
    node_queue.push(nullptr);

    std::deque<int> level_list {};
    bool            is_order_left {true};

    while (not node_queue.empty())
    {
        const auto curr_node = node_queue.front();
        node_queue.pop();

        if (curr_node != nullptr)
        {
            if (is_order_left)
            {
                level_list.push_back(curr_node->val);
            }
            else
            {
                level_list.push_front(curr_node->val);
            }

            if (curr_node->left != nullptr)
            {
                node_queue.push(curr_node->left);
            }

            if (curr_node->right != nullptr)
            {
                node_queue.push(curr_node->right);
            }
        }
        else
        {
            //! We finished the scan of one level
            results.emplace_back(level_list.cbegin(), level_list.cend());
            level_list.clear();

            //! Prepare for the next level
            if (not node_queue.empty())
            {
                node_queue.push(nullptr);
            }

            is_order_left = not is_order_left;

        } // else -> if (curr_node != nullptr)

    } // while (not node_queue.empty())

    return results;

} // static std::vector<std::vector<int>> zigzagLevelOrderBFS( ...

//! @brief Recursive helper function for DFS solution
//! @param[in]  node    Pointer to current node
//! @param[in]  level   Current level in tree
//! @param[out] results Global structure indexed by level containing level nodes
static void DFS_helper(TreeNode*                      node,
                       int                            level,
                       std::vector<std::vector<int>>& results)
{
    if (level >= static_cast<int>(results.size()))
    {
        //! First time we visit any node for level
        //! Create level with current node value as initial element
        results.emplace_back({node->val});
    }
    else
    {
        //! Level exists - depending on ordering, insert current node value
        //! either to head or tail

        if (level % 2 == 0)
        {
            results[level].push_back(node->val);
        }
        else
        {
            results[level].insert(results[level].begin(), node->val);
        }

    } // else -> if (level >= static_cast<int>(results.size()))

    if (node->left != nullptr)
    {
        DFS_helper(node->left, level + 1, results);
    }

    if (node->right != nullptr)
    {
        DFS_helper(node->right, level + 1, results);
    }

} // static void DFS_helper( ...

//! @brief DFS solution to get zigzag level order traversal of nodes' values
//! @param[in] root Pointer to root of binary tree
//! @return Zigzag level order traversal of node values
static std::vector<std::vector<int>> zigzagLevelOrderDFS(TreeNode* root)
{
    //! @details https://leetcode.com/problems/
    //!          binary-tree-zigzag-level-order-traversal/editorial/
    //!
    //!          Time complexity O(N) where N is the number of nodes. We visit
    //!          each node once.
    //!          Space complexity O(N). Unlike the BFS approach we do not need
    //!          to maintain a node_queue. However, the size of the call stack
    //!          for any invocation of DFS_helper(node, level) will be exactly
    //!          level. The space complexity is O(H) where H is the height of
    //!          the tree. In the worst-case when the tree is skewed, the tree
    //!          height could be N. If the tree were guaranteed to be balanced
    //!          then the max height of the tree would be log N which would
    //!          result in a better space complexity than the BFS approach.

    if (root == nullptr)
    {
        return {};
    }

    std::vector<std::vector<int>> results {};
    DFS_helper(root, 0, results);
    return results;

} // static std::vector<std::vector<int>> zigzagLevelOrderDFS( ...

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

    const auto resultBFS = zigzagLevelOrderBFS(&three);
    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           resultBFS.cbegin()));
    
    const auto resultDFS = zigzagLevelOrderDFS(&three);
    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           resultDFS.cbegin()));
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
    
    const auto resultBFS = zigzagLevelOrderBFS(&one);
    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           resultBFS.cbegin()));
    
    const auto resultDFS = zigzagLevelOrderDFS(&one);
    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           resultDFS.cbegin()));
}