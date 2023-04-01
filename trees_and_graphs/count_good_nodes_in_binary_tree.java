public int dfs(TreeNode node, int maxSoFar)
{
    if (node == null)
    {
        return 0;
    }

    int left = dfs(node.left, Math.max(maxSoFar, node.val));
    int right = dfs(node.right, Math.max(maxSoFar, node.val));
    int ans = left + right;
    if (node.val >= maxSoFar)
    {
        ans += 1;
    }

    return ans;
}

public int goodNodesRecursive(TreeNode root)
{
    return dfs(root, Integer.MIN_VALUE);
}