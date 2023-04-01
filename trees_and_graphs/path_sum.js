/**
 * @param {TreeNode} root
 * @param {number} targetSum
 * @returns {boolean}
 */
var hasPathSumRecursive = function(root, targetSum)
{
    let dfs = (node, curr) => {
        if (!node)
        {
            return false;
        }

        // If both children are null then the node is a leaf
        if (!node.left && !node.right)
        {
            return (curr + node.val) == targetSum;
        }

        curr += node.val;
        let left = dfs(node.left, curr);
        let right = dfs(node.right, curr);
        return left || right;
    }

    return dfs(root, 0);
};

/**
 * @param {TreeNode} root
 * @param {number} targetSum
 * @returns {boolean}
 */
var hasPathSumIterative = function(root, targetSum)
{
    if (!root)
    {
        return false;
    }

    let stack = [[root, 0]];
    while (stack.length)
    {
        let [node, curr] = stack.pop();

        // If both children are null then the node is a leaf
        if (!node.left && !node.right && curr + node.val == targetSum)
        {
            return true;
        }

        curr += node.val;
        if (node.left)
        {
            stack.push([node.left, curr]);
        }
        if (node.right)
        {
            stack.push([node.right, curr]);
        }
    }

    return false;
};