/**
 * @param {TreeNode} root
 * @returns {number}
 */
var getMinimumDifferenceRecursive = function(root)
{
    let dfs = node => {
        if (!node)
        {
            return [];
        }

        let left = dfs(node.left);
        const right = dfs(node.right);

        left.push(node.val);
        left.push(...right);
        return left;
    }

    let values = dfs(root);
    let ans = Infinity;
    for (let i = 1; i < values.length; i++)
    {
        ans = Math.min(ans, values[i] - values[i - 1]);
    }

    return ans;
};