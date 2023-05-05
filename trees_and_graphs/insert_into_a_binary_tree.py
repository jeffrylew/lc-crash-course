import treenode

def insertIntoBSTRecursive(
    root: treenode.TreeNode, val: int
) -> treenode.TreeNode:
    if not root:
        return treenode.TreeNode(val)
    
    if val > root.val:
        # Insert into the right subtree
        root.right = insertIntoBSTRecursive(root.right, val)
    else:
        # Insert into the left subtree
        root.left = insertIntoBSTRecursive(root.left, val)
    
    return root

def insertIntoBSTIterative(
    root: treenode.TreeNode, val: int
) -> treenode.TreeNode:
    node = root

    while node:
        # Insert into the right subtree
        if val > node.val:
            # Insert right now
            if not node.right:
                node.right = treenode.TreeNode(val)
                return root
            else:
                node = node.right
        # Insert into the left subtree
        else:
            # Insert right now
            if not node.left:
                node.left = treenode.TreeNode(val)
                return root
            else:
                node = node.left
        
    return treenode.TreeNode(val)