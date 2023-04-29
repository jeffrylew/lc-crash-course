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