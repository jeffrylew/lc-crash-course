/**
 * @param {TreeNode} root
 * @param {number} low
 * @param {number} high
 * @return {number}
 */
var rangeSumBSTRecursive = function(root, low, high)
{
    if (!root)
    {
        return 0;
    }

    let ans = 0;
    if (low <= root.val && root.val <= high)
    {
        ans += root.val;
    }

    if (low < root.val)
    {
        ans += rangeSumBSTRecursive(root.left, low, high);
    }

    if (root.val < high)
    {
        ans += rangeSumBSTRecursive(root.right, low, high);
    }

    return ans;
};

/**
 * @param {TreeNode} root
 * @param {number} low
 * @param {number} high
 * @return {number}
 */
var rangeSumBSTIterative = function(root, low, high)
{
    if (!root)
    {
        return 0;
    }

    let stack = [root];
    let ans = 0;

    while (stack.length)
    {
        const node = stack.pop();
        if (low <= node.val && node.val <= high)
        {
            ans += node.val;
        }

        if (node.left && low < node.val)
        {
            stack.push(node.left);
        }

        if (node.right && node.val < high)
        {
            stack.push(node.right);
        }
    }

    return ans;
};