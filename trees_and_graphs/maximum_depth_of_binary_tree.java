public int maxDepthRecursive(TreeNode root)
{
    if (root = null)
    {
        return 0;
    }

    int left = maxDepthRecursive(root.left);
    int right = maxDepthRecursive(root.right);
    return Math.max(left, right) + 1;
}