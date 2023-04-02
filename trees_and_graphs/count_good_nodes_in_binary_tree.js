/**
 * @param {TreeNode} root
 * @returns {number}
 */
var goodNodesRecursive = function(root)
{
    let dfs = (node, maxSoFar) => {
        if (!node)
        {
            return 0;
        }

        const left = dfs(node.left, Math.max(maxSoFar, node.val));
        const right = dfs(node.right, Math.max(maxSoFar, node.val));
        let ans = left + right;
        if (node.val >= maxSoFar)
        {
            ans++;
        }

        return ans;
    }

    return dfs(root, -Infinity);
};


var goodNodesIterative = function(root)
{
    if (!root)
    {
        return 0;
    }

    let stack = [[root, -Infinity]];
    let ans = 0;

    while (stack.length)
    {
        const [node, maxSoFar] = stack.pop();
        if (node.val >= maxSoFar)
        {
            ans++;
        }

        if (node.left)
        {
            stack.push([node.left, Math.max(maxSoFar, node.val)]);
        }

        if (node.right)
        {
            stack.push([node.right, Math.max(maxSoFar, node.val)]);
        }
    }

    return ans;
};