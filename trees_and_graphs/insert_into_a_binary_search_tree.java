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

public TreeNode insertIntoBSTIterative(TreeNode root, int val)
{
    TreeNode node = root;

    while (node != null)
    {
        if (val > node.val)
        {
            // Insert into the right subtree
            // Insert right now
            if (node.right == null)
            {
                node.right = new TreeNode(val);
                return root;
            }
            else
            {
                node = node.right;
            }
        }
        else
        {
            // Insert into the left subtree
            // Insert right now
            if (node.left == null)
            {
                node.left = new TreeNode(val);
                return root;
            }
            else
            {
                node = node.left;
            }
        }
    }

    return new TreeNode(val);
}