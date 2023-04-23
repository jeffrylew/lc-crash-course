public List<Integer> dfs(TreeNode node)
{
    if (node == null)
    {
        return new ArrayList<>();
    }

    List<Integer> left = dfs(node.left);
    List<Integer> right = dfs(node.right);

    left.add(node.val);
    left.addAll(right);
    return left;
}

public int getMinimumDifferenceRecursive(TreeNode root)
{
    List<Integer> values = dfs(root);
    int ans = Integer.MAX_VALUE;
    for (int i = 1; i < values.size(); i++)
    {
        ans = Math.min(ans, values.get(i) - values.get(i - 1));
    }

    return ans;
}

public List<Integer> iterativeInorder(TreeNode root)
{
    Stack<TreeNode> stack = new Stack<>();
    List<Integer> values = new ArrayList<>();
    TreeNode curr = root;

    while (!stack.isEmpty() || curr != null)
    {
        if (curr != null)
        {
            stack.push(curr);
            curr = curr.left;
        }
        else
        {
            curr = stack.pop();
            values.add(curr.val);
            curr = curr.right;
        }
    }

    return values;
}

public int getMinimumDifferenceIterative(TreeNode root)
{
    List<Integer> values = iterativeInorder(root);
    int ans = Integer.MAX_VALUE;
    for (int i = 1; i < values.size(); i++)
    {
        ans = Math.min(ans, values.get(i) - values.get(i - 1));
    }

    return ans;
}