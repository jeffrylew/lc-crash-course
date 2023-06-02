#include "treenode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

//! @brief Recursive dfs helper to populate parents map with parent nodes
//! @param[in]  node    Pointer to current TreeNode
//! @param[in]  parent  Pointer to parent of current TreeNode
//! @param[out] parents Reference to map of nodes to their parents
static void dfs(TreeNode*                                 node,
                TreeNode*                                 parent,
                std::unordered_map<TreeNode*, TreeNode*>& parents)
{
    if (node == nullptr)
    {
        return;
    }

    parents[node] = parent;
    dfs(node->left, node, parents);
    dfs(node->right, node, parents);
}

//! @brief Get vector of node values that have a distance k from the target node
//! @param[in] root   Pointer to root of binary tree
//! @param[in] target Pointer to target node in tree
//! @param[in] k      Distance from target node
//! @return Vector of values of all nodes that are distance k from target
static std::vector<int> distanceK(TreeNode* root, TreeNode* target, int k)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /707/traversals-trees-graphs/4631/
    //!
    //!          Time complexity O(N). Both DFS and BFS perform constant work at
    //!          each node and visit each node at most once.
    //!          Space complexity O(N) for recursion call stack when assigning
    //!          parents. Also for queue and seen.

    std::unordered_map<TreeNode*, TreeNode*> parents {};
    dfs(root, nullptr, parents);

    std::queue<TreeNode*>         queue {};
    std::unordered_set<TreeNode*> seen {};
    queue.push(target);
    seen.insert(target);

    int distance {};
    while (not queue.empty() && distance < k)
    {
        const auto currentLength = static_cast<int>(queue.size());
        for (int i = 0; i < currentLength; ++i)
        {
            const TreeNode* node {queue.front()};
            queue.pop();

            for (const auto neighbor : {node->left, node->right, parents[node]})
            {
                if (neighbor != nullptr && seen.count(neighbor) == 0)
                {
                    seen.insert(neighbor);
                    queue.push(neighbor);
                }
            }
        }

        ++distance;
    }

    std::vector<int> ans {};
    while (not queue.empty())
    {
        const Treenode* node {queue.front()};
        queue.pop();
        ans.push_back(node->val);
    }

    return ans;

} // static std::vector<int> distanceK( ...

TEST(DistanceKTest, SampleTest)
{
    TreeNode one {1};
    TreeNode two {2};
    TreeNode three {3};
    TreeNode five {5};

    const TreeNode zero {0};
    const TreeNode four {4};
    const TreeNode six {6};
    const TreeNode seven {7};
    const TreeNode eight {8};

    three.left  = &five;
    three.right = &one;

    five.left  = &six;
    five.right = &two;

    two.left  = &seven;
    two.right = &four;

    one.left  = &zero;
    one.right = &eight;

    const std::vector<int> expected_output {1, 4, 7};

    auto result = distanceK(&three, &five, 2);
    std::sort(result.begin(), result.end());

    EXPECT_EQ(result, expected_output);
}