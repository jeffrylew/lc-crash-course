class Solution
{
    constructor(diameter)
    {
        this.diameter = diameter;
    }

    /**
     * @param {TreeNode} node
     * @returns {number}
     */
    longestPath(node)
    {
        if (!node)
        {
            return 0;
        }

        // Recursively find the longest path in both left and right child
        const leftPath = longestPath(node.left);
        const rightPath = longestPath(node.right);

        // Update diameter if leftPath plus rightPath is larger
        this.diameter = Math.max(this.diameter, leftPath + rightPath);

        // Return longer between leftPath and rightPath
        // Remember to add 1 for path connecting node and its parent
        return Math.max(leftPath, rightPath) + 1;
    };

    /**
     * @param {TreeNode} root
     * @returns {number}
     */
    diameterOfBinaryTree(root)
    {
        this.diameter = 0;
        longestPath(root);
        return this.diameter;
    };
}