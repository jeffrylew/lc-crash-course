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

class Pair
{
    TreeNode node;
    int maxSoFar;

    Pair(TreeNode node, int maxSoFar)
    {
        this.node = node;
        this.maxSoFar = maxSoFar;
    }
}

public int goodNodesIterative(TreeNode root)
{
    if (root == null)
    {
        return 0;
    }

    Stack<Pair> stack = new Stack<>();
    stack.push(new Pair(root, Integer.MIN_VALUE));
    int ans = 0;

    while (!stack.empty())
    {
        Pair pair = stack.pop();
        TreeNode node = pair.node;
        int maxSoFar = pair.maxSoFar;
        if (node.val >= maxSoFar)
        {
            ans++;
        }

        if (node.left != null)
        {
            stack.push(new Pair(node.left, Math.max(maxSoFar, node.val)));
        }

        if (node.right != null)
        {
            stack.push(new Pair(node.right, Math.max(maxSoFar, node.val)));
        }
    }

    return ans;
}