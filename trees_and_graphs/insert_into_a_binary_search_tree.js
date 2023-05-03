import TreeNode from "./treenode";

/**
 * @param {TreeNode} root
 * @param {number} val
 * @returns {TreeNode}
 */
var insertIntoBSTRecursive = function(root, val)
{
    if (!root)
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
};

/**
 * @param {TreeNode} root
 * @param {number} val
 * @returns {TreeNode}
 */
var insertIntoBSTIterative = function(root, val)
{
    let node = root;

    while (node)
    {
        if (val > node.val)
        {
            // Insert into the right subtree
            if (!node.right)
            {
                // Insert right now
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
            if (!node.left)
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
};