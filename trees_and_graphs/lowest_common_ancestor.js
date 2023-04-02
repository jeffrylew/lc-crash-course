/**
 * @param {TreeNode} root
 * @param {TreeNode} p
 * @param {TreeNode} q
 * @returns {TreeNode}
 */
var lowestCommonAncestorRecursive = function(root, p, q)
{
    if (!root)
    {
        return null;
    }

    if (root == p || root == q)
    {
        return root;
    }

    const left = lowestCommonAncestorRecursive(root.left, p, q);
    const right = lowestCommonAncestorRecursive(root.right, p, q);

    if (left && right)
    {
        return root;
    }

    if (left)
    {
        return left;
    }

    return right;
}