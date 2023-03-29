var maxDepthRecursive = function(root) {
    if (!root)
    {
        return 0;
    }

    const left = maxDepthRecursive(root.left);
    const right = maxDepthRecursive(root.right);
    return Math.max(left, right) + 1;
};

var maxDepthIterative = function(root) {
    if (!root)
    {
        return 0;
    }

    let stack = [[root, 1]];
    let ans = 0;

    while (stack.length)
    {
        const [node, depth] = stack.pop();
        ans = Math.max(ans, depth);

        if (node.left)
        {
            stack.push([node.left, depth + 1]);
        }

        if (node.right)
        {
            stack.push([node.right, depth + 1]);
        }
    }

    return ans;
};