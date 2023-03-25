public void inorderDfs(TreeNode node)
{
    if (node == null)
    {
        return;
    }

    inorderDfs(node.left);
    System.out.println(node.val);
    inorderDfs(node.right);
}