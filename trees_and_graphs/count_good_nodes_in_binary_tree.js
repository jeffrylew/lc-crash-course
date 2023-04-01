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