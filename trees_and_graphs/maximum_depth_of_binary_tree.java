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

class Pair
{
    TreeNode node;
    int depth;

    Pair(TreeNode node, int depth)
    {
        this.node = node;
        this.depth = depth;
    }
}

public int maxDepthIterative(TreeNode root)
{
    if (root == null)
    {
        return 0;
    }

    Stack<Pair> stack = new Stack<>();
    stack.push(new Pair(root, 1));
    int ans = 0;

    while (!stack.empty())
    {
        Pair pair = stack.pop();
        TreeNode node = pair.node;
        int depth = pair.depth;

        ans = Math.max(ans, depth);
        if (node.left != null)
        {
            stack.push(new Pair(node.left, depth + 1));
        }
        if (node.right != null)
        {
            stack.push(new Pair(node.right, depth + 1));
        }
    }

    return ans;
}