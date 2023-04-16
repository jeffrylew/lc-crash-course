/**
 * @param {TreeNode} root
 * @return {number}
 */
var deepestLeavesSumDFS = function(root) {
    let deepestSum = 0;
    let depth = 0;

    let stack = [[root, 0]];

    while (stack.length)
    {
        const [node, currDepth] = stack.pop();

        if (!node.left && !node.right)
        {
            // If this leaf is the deepest one seen so far
            if (depth < currDepth)
            {
                // Start new sum
                deepestSum = node.val;

                // Note new depth
                depth = currDepth;
            }
            else if (depth == currDepth)
            {
                // If there were already leaves at this depth,
                // update existing sum
                deepestSum += node.val;
            }
        }
        else
        {
            if (node.right)
            {
                stack.push([node.right, currDepth + 1]);
            }

            if (node.left)
            {
                stack.push([node.left, currDepth + 1]);
            }
        }
    }

    return deepestSum;
};

/**
 * @param {TreeNode} root
 * @return {number}
 */
var deepestLeavesSumBFS = function(root) {
    let nextLevel = [root];
    let currLevel = [];

    while (nextLevel.length)
    {
        // Prepare for the next level
        currLevel = [...nextLevel];
        nextLevel = [];

        for (const node of currLevel)
        {
            // Add child nodes of the current level
            // in the queue for the next level
            if (node.left)
            {
                nextLevel.push(node.left);
            }

            if (node.right)
            {
                nextLevel.push(node.right);
            }
        }
    }

    let deepestSum = 0;
    for (const node of currLevel)
    {
        deepestSum += node.val;
    }
    return deepestSum;
};