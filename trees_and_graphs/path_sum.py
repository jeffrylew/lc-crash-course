import treenode

def hasPathSumRecursive(root: treenode.TreeNode, targetSum: int) -> bool:
    def dfs(node, curr):
        if not node:
            return False
        
        # If both children are null then the node is a leaf
        if node.left == None and node.right == None:
            return (curr + node.val) == targetSum
        
        curr += node.val
        left = dfs(node.left, curr)
        right = dfs(node.right, curr)
        return left or right
    
    return dfs(root, 0)

def hasPathSumIterative(root: treenode.TreeNode, targetSum: int) -> bool:
    if not root:
        return False
    
    stack = [(root, 0)]
    while stack:
        node, curr = stack.pop()

        # If both children are null then the node is a leaf
        if node.left == None and node.right == None:
            if (curr + node.val) == targetSum:
                return True
        
        curr += node.val
        if node.left:
            stack.append((node.left, curr))

        if node.right:
            stack.append((node.right, curr))
    
    return False