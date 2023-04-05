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

def minDepthDFSIterative(root: treenode.TreeNode) -> int:
    """
    :type root: TreeNode
    :rtype: int
    """
    if not root:
        return 0
    
    stack, min_depth = [(root, 1),], float('inf')

    while stack:
        curr, current_depth = stack.pop()
        children = [curr.left, curr.right]

        if not any(children):
            min_depth = min(min_depth, current_depth)
        
        for node in children:
            if node:
                stack.append((node, current_depth + 1))
    
    return min_depth