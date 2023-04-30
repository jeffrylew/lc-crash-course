public TreeNode insertIntoBSTRecursive(TreeNode root, int val)
{
    if (root == null)
    {
        return new TreeNode(val);
    }

    if (val > root.val)
    {
        // Insert into the right subtree
        root.right = insertIntoBSTRecursive(root.right, val);
    }
    else
    {
        // Insert into the left subtree
        root.left = insertIntoBSTRecursive(root.left, val);
    }
    
    return root;
}