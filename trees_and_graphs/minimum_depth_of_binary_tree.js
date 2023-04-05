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

const minDepthDFSIterative = (root) => {
    if (!root)
    {
        return 0;
    }

    let stack = [[root, 1]];
    let min_depth = Number.MAX_SAFE_INTEGER;

    while (stack.length)
    {
        const [node, current_depth] = stack.pop();
        if (!node.left && !node.right)
        {
            min_depth = Math.min(min_depth, current_depth);
        }

        if (node.left)
        {
            stack.push([node.left, current_depth + 1]);
        }

        if (node.right)
        {
            stack.push([node.right, current_depth + 1]);
        }
    }

    return min_depth;
};

const minDepthBFSIterative = (root) => {
    if (!root)
    {
        return 0;
    }

    let queue = [[root, 1]];
    let current_depth = 0;

    while (queue.length)
    {
        const [node, depth] = queue.shift();
        current_depth = depth;
        if (!node.left && !node.right)
        {
            break;
        }

        if (node.left)
        {
            queue.push([node.left, current_depth + 1]);
        }

        if (node.right)
        {
            queue.push([node.right, current_depth + 1]);
        }
    }

    return current_depth;
};