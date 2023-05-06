/**
 * @param {TreeNode} root
 * @param {number} target
 * @return {number}
 */
var closestValueRecursive = function(root, target)
{
    const inorder = (node, nums) => {
        if (!node)
        {
            return;
        }

        inorder(node.left, nums);
        nums.push(node.val);
        inorder(node.right, nums);
    }

    let nums = [];
    inorder(root, nums);

    // Need to use <= instead of < to get smallest value that is closest to the
    // target. e.g. if target = 3.5 and BST contains 3 and 4, should return 3
    return nums.reduce(
        (prev, curr) => Math.abs(prev - target) <= Math.abs(curr - target)
        ? prev : curr);
};