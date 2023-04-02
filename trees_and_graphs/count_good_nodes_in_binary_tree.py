import treenode

def goodNodesIterative(root: treenode.TreeNode) -> int:
    def dfs(node, max_so_far):
        if not node:
            return 0
        
        left = dfs(node.left, max(max_so_far, node.val))
        right = dfs(node.right, max(max_so_far, node.val))
        ans = left + right
        if node.val >= max_so_far:
            ans += 1
        
        return ans
    
    return dfs(root, float("-inf"))