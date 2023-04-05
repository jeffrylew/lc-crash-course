const minDepthRecursive = (root) => {
    if (!root)
    {
        return 0;
    }

    if (!root.left && !root.right)
    {
        return 1;
    }

    let min_depth = Number.MAX_SAFE_INTEGER;

    if (root.left)
    {
        min_depth = Math.min(minDepthRecursive(root.left), min_depth);
    }

    if (root.right)
    {
        min_depth = Math.min(minDepthRecursive(root.right), min_depth);
    }

    return min_depth + 1;
};