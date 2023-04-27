import treenode

def getMinimumDifference(root: treenode.TreeNode) -> int:
    def dfs(node: treenode.TreeNode) -> list[int]:
        if not node:
            return []
        
        left = dfs(node.left)
        right = dfs(node.right)
        return left + [node.val] + right
    
    values = dfs(root)
    ans = float("inf")
    for i in range(1, len(values)):
        ans = min(ans, values[i] - values[i - 1])
    
    return ans