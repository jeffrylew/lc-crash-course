public void preorderDfs(Node node)
{
    if (node == null)
    {
        return;
    }

    System.out.println(node.val);
    preorderDfs(node.left);
    preorderDfs(node.right);
}