public void dfs(Node node)
{
    if (node == null)
    {
        return;
    }

    dfs(node.left);
    dfs(node.right);
}