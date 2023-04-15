/**
 * @param {TreeNode} root
 * @returns {number[]}
 */
var largestValues = function(root) {
    if (!root)
    {
        return [];
    }

    let ans = [];
    let queue = [root];

    while (queue.length)
    {
        const currentLength = queue.length;
        let currMax = Number.MIN_SAFE_INTEGER;
        // let currMax = -Infinity;
        let nextQueue = [];

        for (let i = 0; i < currentLength; i++)
        {
            const node = queue.shift();
            // const node = queue[i];
            currMax = Math.max(currMax, node.val);

            if (node.left)
            {
                nextQueue.push(node.left);
            }

            if (node.right)
            {
                nextQueue.push(node.right);
            }
        }

        ans.push(currMax);
        queue = nextQueue;
    }

    return ans;
};