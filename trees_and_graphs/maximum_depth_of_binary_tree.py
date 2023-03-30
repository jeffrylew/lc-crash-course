import treenode

def maxDepthRecursive(root: treenode.TreeNode) -> int:
    if not root:
        return 0
    
    left = maxDepthRecursive(root.left)
    right = maxDepthRecursive(root.right)
    return max(left, right) + 1

def maxDepthIterative(root: treenode.TreeNode) -> int:
    if not root:
        return 0
    
    stack = [(root, 1)]
    ans = 0

    while stack:
        node, depth = stack.pop()
        ans = max(ans, depth)

        if node.left:
            stack.append((node.left, depth + 1))
        
        if node.right:
            stack.append((node.right, depth + 1))
    
    return ans