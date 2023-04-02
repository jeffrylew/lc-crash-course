import treenode

def lowestCommonAncestorRecursive(root: treenode.TreeNode,
                                  p: treenode.TreeNode,
                                  q: treenode.TreeNode) -> treenode.TreeNode:
    if not root:
        return None
    
    if root == p or root == q:
        return root
    
    left = lowestCommonAncestorRecursive(root.left, p, q)
    right = lowestCommonAncestorRecursive(root.right, p, q)

    if left and right:
        return root
    
    if left:
        return left
    
    return right