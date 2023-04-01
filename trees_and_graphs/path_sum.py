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