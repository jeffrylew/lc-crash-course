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

class State
{
    TreeNode node;
    long small;
    long large;

    State(TreeNode node, long small, long large)
    {
        this.node = node;
        this.small = small;
        this.large = large;
    }
}

public boolean isValidBSTIterative(TreeNode root)
{
    Stack<State> stack = new Stack<>();
    stack.push(new State(root, Long.MIN_VALUE, Long.MAX_VALUE));

    while (!stack.empty())
    {
        State state = stack.pop();
        TreeNode node = state.node;
        long small = state.small;
        long large = state.large;

        if (small >= node.val || node.val >= large)
        {
            return false;
        }

        if (node.left != null)
        {
            stack.push(new State(node.left, small, node.val));
        }

        if (node.right != null)
        {
            stack.push(new State(node.right, node.val, large));
        }
    }

    return true;
}