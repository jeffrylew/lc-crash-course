import treenode

def minDepthRecursive(root: treenode.TreeNode) -> int:
    """
    :type root: TreeNode
    :rtype: int
    """
    if not root:
        return 0
    
    children = [root.left, root.right]

    # If we're at a leaf node
    if not any(children):
        return 1
    
    min_depth = float('inf')
    for node in children:
        if node:
            min_depth = min(minDepthRecursive(node), min_depth)

    return min_depth + 1
