public boolean dfs(TreeNode node, long small, long large)
{
    if (node == null)
    {
        return true;
    }

    if (small >= node.val || node.val >= large)
    {
        return false;
    }

    boolean left = dfs(node.left, small, node.val);
    boolean right = dfs(node.right, node.val, large);
    return left && right;
}

public boolean isValidBSTRecursive(TreeNode root)
{
    return dfs(root, Long.MIN_VALUE, Long.MAX_VALUE);
}