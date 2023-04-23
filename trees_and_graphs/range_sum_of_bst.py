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