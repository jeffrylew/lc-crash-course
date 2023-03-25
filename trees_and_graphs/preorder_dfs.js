let preorderDfs = node => {
    if (!node)
    {
        return;
    }

    console.log(node.val);
    preorderDfs(node.left);
    preorderDfs(node.right);
}