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

/**
 * @param {TreeNode} root
 * @param {number} target
 * @return {number}
 */
var closestValueIterative = function(root, target)
{
    let stack = [];
    let pred = Number.MIN_SAFE_INTEGER;

    while (stack.length || root)
    {
        while (root)
        {
            stack.push(root);
            root = root.left;
        }
        root = stack.pop();
        
        if (pred <= target && target < root.val)
        {
            // Need to use <= instead of < to get smallest value that is closest
            // to the target. e.g. target = 3.5, BST contains 3 and 4, return 3
            return Math.abs(pred - target) <= Math.abs(root.val - target)
                ? pred : root.val;
        }

        pred = root.val;
        root = root.right;
    }
    
    return pred;
};

/**
 * @param {TreeNode} root
 * @param {number} target
 * @return {number}
 */
var closestValueBinarySearch = function(root, target)
{
    let val = root.val;
    let closest = root.val;

    while (root)
    {
        val = root.val;

        // Editorial is incorrect here, fixed now
        const val_diff = Math.abs(val - target);
        const close_diff = Math.abs(closest - target);

        if (val_diff < close_diff)
        {
            closest = val;
        }
        else if (val_diff == close_diff)
        {
            closest = Math.min(val, closest);
        }

        root = target < root.val ? root.left : root.right;
    }

    return closest;
};