import treenode

def isValidBSTRecursive(root: treenode.TreeNode) -> bool:
    def dfs(node, small, large):
        if not node:
            return True
        
        if not (small < node.val < large):
            return False
        
        left = dfs(node.left, small, node.val)
        right = dfs(node.right, node.val, large)

        # Tree is a BST if left and right subtrees are also BSTs
        return left and right
    
    return dfs(root, float("-inf"), float("inf"))