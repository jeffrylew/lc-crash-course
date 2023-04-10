class Solution
{
    private int diameter;

    public int diameterOfBinaryTree(TreeNode root)
    {
        diameter = 0;
        longestPath(root);
        return diameter;
    }

    private int longestPath(TreeNode node)
    {
        if (node == null)
        {
            return 0;
        }

        // Recursively find the longest path in both left and right children
        int leftPath = longestPath(node.left);
        int rightPath = longestPath(node.right);

        // Update diameter if leftPath plus rightPath is larger
        diameter = Math.max(diameter, leftPath + rightPath);

        // Return longer of leftPath and rightPath
        // Remember to add 1 for path connecting node and its parent
        return Math.max(leftPath, rightPath) + 1;
    }
}