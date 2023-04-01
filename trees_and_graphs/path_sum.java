public boolean dfs(TreeNode node, int targetSum, int curr)
{
    if (node == null)
    {
        return false;
    }

    if (node.left == null && node.right == null)
    {
        return (curr + node.val) == targetSum;
    }

    curr += node.val;
    boolean left = dfs(node.left, targetSum, curr);
    boolean right = dfs(node.right, targetSum, curr);
    return left || right;
}

public boolean hasPathSumRecursive(TreeNode root, int targetSum)
{
    return dfs(root, targetSum, 0);
}