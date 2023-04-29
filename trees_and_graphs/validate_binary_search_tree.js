/**
 * @param {TreeNode} root
 * @returns {boolean}
 */
var isValidBSTRecursive = function(root)
{
    let dfs = (node, small, large) => {
        if (!node)
        {
            return true;
        }

        if (small >= node.val || node.val >= large)
        {
            return false;
        }

        const left = dfs(node.left, small, node.val);
        const right = dfs(node.right, node.val, large);

        // Tree is a BST if left and right subtrees are also BSTs
        return left && right;
    }

    return dfs(root, -Infinity, Infinity);
};

/**
 * @param {TreeNode} root
 * @returns {boolean}
 */
var isValidBSTIterative = function(root)
{
    let stack = [[root, -Infinity, Infinity]];

    while (stack.length)
    {
        const [node, small, large] = stack.pop();

        if (small >= node.val || node.val >= large)
        {
            return false;
        }

        if (node.left)
        {
            stack.push([node.left, small, node.val]);
        }

        if (node.right)
        {
            stack.push([node.right, node.val, large]);
        }
    }

    return true;
};