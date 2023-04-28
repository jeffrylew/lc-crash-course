import treenode

def getMinimumDifferenceRecursive(root: treenode.TreeNode) -> int:
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

def getMinimumDifferenceIterative(root: treenode.TreeNode) -> int:
    def iterative_inorder(root):
        stack = []
        values = []
        curr = root

        while stack or curr:
            if curr:
                stack.append(curr)
                curr = curr.left
            else:
                curr = stack.pop()
                values.append(curr.val)
                curr = curr.right

        return values
    
    values = iterative_inorder(root)
    ans = float("inf")
    for i in range(1, len(values)):
        ans = min(ans, values[i] - values[i - 1])
    
    return ans