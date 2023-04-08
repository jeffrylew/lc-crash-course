class Solution
{
    constructor(result)
    {
        this.result = result;
    }

    helper1(node, curMax, curMin) {
        if (!node)
        {
            return;
        }

        const possibleResult = Math.max(Math.abs(curMax - node.val),
                                        Math.abs(curMin - node.val));
        
        this.result = Math.max(this.result, possibleResult);

        curMax = Math.max(curMax, node.val);
        curMin = Math.min(curMin, node.val);

        this.helper1(node.left, curMax, curMin);
        this.helper1(node.right, curMax, curMin);
    };
    
    /**
     * @param {TreeNode} root
     * @return {number}
     */
    maxAncestorDiff1(root) {
        if (!root)
        {
            return 0;
        }

        this.result = 0;
        this.helper1(root, root.val, root.val);
        return this.result;
    };
}