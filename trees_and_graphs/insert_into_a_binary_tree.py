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