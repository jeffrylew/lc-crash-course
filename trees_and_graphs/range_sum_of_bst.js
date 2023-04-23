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