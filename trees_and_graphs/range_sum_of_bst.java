public int rangeSumBSTRecursive(TreeNode root, int low, int high)
{
    if (root == null)
    {
        return 0;
    }

    int ans = 0;
    if (low <= root.val && root.val <= high)
    {
        ans += root.val;
    }

    if (low < root.val)
    {
        ans += rangeSumBSTRecursive(root.left, low, high);
    }

    if (root.val < high)
    {
        ans += rangeSumBSTRecursive(root.right, low, high);
    }

    return ans;
}