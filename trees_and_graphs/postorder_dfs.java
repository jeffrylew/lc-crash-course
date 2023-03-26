public void postorderDfs(TreeNode node)
{
    if (node == null)
    {
        return;
    }

    postorderDfs(node.left);
    postorderDfs(node.right);
    System.out.println(node.val);
}