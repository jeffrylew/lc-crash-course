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

/**
 * @param {TreeNode} root
 * @returns {number}
 */
var getMinimumDifferenceIterative = function(root)
{
    let iterativeInorder = root => {
        let stack = [];
        let values = [];
        let curr = root;

        while (stack.length || curr)
        {
            if (curr)
            {
                stack.push(curr);
                curr = curr.left;
            }
            else
            {
                curr = stack.pop();
                values.push(curr.val);
                curr = curr.right;
            }
        }

        return values;
    }

    let values = iterativeInorder(root);
    let ans = Infinity;
    for (let i = 1; i < values.length; i++)
    {
        ans = Math.min(ans, values[i] - values[i - 1]);
    }

    return ans;
};