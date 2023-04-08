class Solution
{
    // Record the required maximum difference
    int result = 0;

    public void helper1(TreeNode node, int curMax, int curMin)
    {
        if (node == null)
        {
            return;
        }

        // Update result
        int possibleResult = Math.max(Math.abs(curMax - node.val),
                                      Math.abs(curMin - node.val));
        result = Math.max(result, possibleResult);

        // Update the max and min
        curMax = Math.max(curMax, node.val);
        curMin = Math.min(curMin, node.val);

        helper1(node.left, curMax, curMin);
        helper1(node.right, curMax, curMin);
    }

    public int maxAncestorDiff1(TreeNode root)
    {
        if (root == null)
        {
            return 0;
        }

        result = 0;
        helper1(root, root.val, root.val);
        return result;
    }
}