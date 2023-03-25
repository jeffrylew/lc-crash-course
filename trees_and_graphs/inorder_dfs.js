let inorderDfs = node => {
    if (!node)
    {
        return;
    }

    inorderDfs(node.left);
    console.log(node.val);
    inorderDfs(node.right);
}