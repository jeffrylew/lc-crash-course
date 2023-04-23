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

public int rangeSumBSTIterative(TreeNode root, int low, int high)
{
    if (root == null)
    {
        return 0;
    }
    
    Stack<TreeNode> stack = new Stack<>();
    stack.push(root);
    int ans = 0;

    while (!stack.empty())
    {
        TreeNode node = stack.pop();

        if (low <= node.val && node.val <= high)
        {
            ans += node.val;
        }

        if (node.left != null && low < node.val)
        {
            stack.push(node.left);
        }

        if (node.right != null && node.val < high)
        {
            stack.push(node.right);
        }
    }

    return ans;
}