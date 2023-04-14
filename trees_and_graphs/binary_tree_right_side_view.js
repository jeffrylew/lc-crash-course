/**
 * @param {TreeNode} root
 * @returns {number[]}
 */
var rightSideView = function(root) {
    if (!root)
    {
        return [];
    }

    let ans = [];
    let queue = [root];

    while (queue.length)
    {
        const nodesInCurrentLevel = queue.length;
        let nextQueue = [];

        // This is the rightmost node for the current level
        ans.push(queue[queue.length - 1].val);

        for (let i = 0; i < nodesInCurrentLevel; i++)
        {
            const node = queue.shift();
            // const node = queue[i];

            if (node.left)
            {
                nextQueue.push(node.left);
            }

            if (node.right)
            {
                nextQueue.push(node.right);
            }
        }

        queue = nextQueue;
    }

    return ans;
};