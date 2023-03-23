let dfs = node => {
    if (!node)
    {
        return;
    }

    dfs(node.left);
    dfs(node.right);
}