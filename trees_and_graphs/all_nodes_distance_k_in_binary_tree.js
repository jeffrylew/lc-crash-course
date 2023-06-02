/**
 * @param {TreeNode} root
 * @param {TreeNode} target
 * @param {number} k
 * @return {number[]}
 */
var distanceK = function(root, target, k)
{
    let parents = new Map();

    const dfs = (node, parent) => {
        if (!node)
        {
            return;
        }

        parents.set(node, parent);
        // Alternatively,
        // node.parent = parent;

        dfs(node.left, node);
        dfs(node.right, node);
    }

    dfs(root, null);

    let queue = [target];
    let seen = new Set([target]);
    let distance = 0;

    while (queue.length && distance < k)
    {
        let currentLength = queue.length;
        let nextQueue = [];

        for (let i = 0; i < currentLength; i++)
        {
            const node = queue[i];

            for (const neighbor of [node.left, node.right, parents.get(node)])
            // for (const neighbor of [node.left, node.right, node.parent])
            {
                if (neighbor && !seen.has(neighbor))
                {
                    seen.add(neighbor);
                    nextQueue.push(neighbor);
                }
            }
        }

        queue = nextQueue;
        distance++;
    }

    return queue.map(node => node.val);
};