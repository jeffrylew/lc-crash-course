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

class Pair
{
    TreeNode node;
    int curr;
    Pair(TreeNode node, int curr)
    {
        this.node = node;
        this.curr = curr;
    }
}

public boolean hasPathSumIterative(TreeNode root, int targetSum)
{
    if (root == null)
    {
        return false;
    }

    Stack<Pair> stack = new Stack<>();
    stack.push(new Pair(root, 0));

    while (!stack.empty())
    {
        Pair pair = stack.pop();
        TreeNode node = pair.node;
        int curr = pair.curr;

        if (node.left == null
            && node.right == null
            && curr + node.val == targetSum)
        {
            return true;
        }

        curr += node.val;
        if (node.left != null)
        {
            stack.push(new Pair(node.left, curr));
        }

        if (node.right != null)
        {
            stack.push(new Pair(node.right, curr));
        }
    }

    return false;
}