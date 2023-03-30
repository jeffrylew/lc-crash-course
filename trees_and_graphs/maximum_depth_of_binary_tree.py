import treenode

def maxDepthRecursive(root: treenode.TreeNode) -> int:
    if not root:
        return 0
    
    left = maxDepthRecursive(root.left)
    right = maxDepthRecursive(root.right)
    return max(left, right) + 1