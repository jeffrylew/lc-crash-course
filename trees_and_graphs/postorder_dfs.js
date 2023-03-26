let postorderDfs = node => {
    if (!node)
    {
        return;
    }

    postorderDfs(node.left);
    postorderDfs(node.right);
    console.log(node.val);
}