import treenode

def rangeSumBSTRecursive(root: treenode.TreeNode, low: int, high: int) -> int:
    if not root:
        return 0
    
    ans = 0
    if low <= root.val <= high:
        ans += root.val

    if low < root.val:
        ans += rangeSumBSTRecursive(root.left, low, high)
    
    if root.val < high:
        ans += rangeSumBSTRecursive(root.right, low, high)

    return ans

def rangeSumBSTIterative(root: treenode.TreeNode, low: int, high: int) -> int:
    if not root:
        return 0
    
    stack = [root]
    ans = 0
    while stack:
        node = stack.pop()

        if low <= node.val <= high:
            ans += node.val

        if node.left and low < node.val:
            stack.append(node.left)
        
        if node.right and node.val < high:
            stack.append(node.right)
    
    return ans