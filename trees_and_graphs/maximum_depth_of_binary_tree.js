var maxDepthRecursive = function(root) {
    if (!root)
    {
        return 0;
    }

    const left = maxDepthRecursive(root.left);
    const right = maxDepthRecursive(root.right);
    return Math.max(left, right) + 1;
};