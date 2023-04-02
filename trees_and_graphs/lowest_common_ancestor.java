public TreeNode lowestCommonAncestorRecursive(TreeNode root,
                                              TreeNode p,
                                              TreeNode q)
{
    if (root == null)
    {
        return null;
    }

    if (root == p || root == q)
    {
        return root;
    }

    TreeNode left = lowestCommonAncestorRecursive(root.left, p, q);
    TreeNode right = lowestCommonAncestorRecursive(root.right, p, q);

    if (left != null && right != null)
    {
        return root;
    }

    if (left != null)
    {
        return left;
    }

    return right;
}