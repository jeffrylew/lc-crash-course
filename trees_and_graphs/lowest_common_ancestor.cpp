#include "treenode.hpp"

#include <gtest/gtest.h>

//! @brief Find lowest common ancestor of p and q (has them as descendants)
//! @param[in] root Pointer to root of binary tree
//! @param[in] p    Pointer to node that is a descendant
//! @param[in] q    Pointer to another node that is a descendant
//! @return Lowest common ancestor of p and q
static TreeNode* lowestCommonAncestorRecursive(TreeNode* root,
                                               TreeNode* p,
                                               TreeNode* q)
{
    //! Base case - empty tree has no LCA
    if (root == nullptr)
    {
        return nullptr;
    }

    //! Case 1: root node is p or q. Answer cannot be below the root node else
    //!         it would be missing the root (p or q) as a descendant. Don't
    //!         need to worry about subtrees at all
    if (root == p || root == q)
    {
        return root;
    }

    auto left  = lowestCommonAncestorRecursive(root->left, p, q);
    auto right = lowestCommonAncestorRecursive(root->right, p, q);

    //! Case 2: One of p or q is in the left subtree and the other is in the
    //!         right subtree. root must be the answer since it is connection
    //!         point between two subtrees. i.e. lowest node to have both p and
    //!         q as descendants
    if (left != nullptr && right != nullptr)
    {
        return root;
    }

    //! Case 3: Both p and q are in one of the subtrees. root is not the answer
    //!         since can look inside the subtree and find a "lower" node
    if (left != nullptr)
    {
        return left;
    }

    return right;
}

TEST(LowestCommonAncestorTest, SampleTest)
{
    const TreeNode zero {0};
    const TreeNode four {4};
    const TreeNode six {6};
    const TreeNode seven {7};
    const TreeNode eight {8};

    TreeNode one {1};
    TreeNode two {2};
    TreeNode three {3};
    TreeNode five {5};

    three.left  = &five;
    three.right = &one;

    five.left  = &six;
    five.right = &two;

    two.left  = &seven;
    two.right = &four;

    one.left  = &zero;
    one.right = &eight;

    const auto lca1 = lowestCommonAncestorRecursive(&three, &six, &two);
    EXPECT_EQ(5, lca1->val);

    const auto lca2 = lowestCommonAncestorRecursive(&three, &one, &eight);
    EXPECT_EQ(1, lca2->val);

    const auto lca3 = lowestCommonAncestorRecursive(&three, &seven, &zero);
    EXPECT_EQ(3, lca3->val);
}