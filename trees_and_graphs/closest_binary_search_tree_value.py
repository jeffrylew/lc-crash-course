import treenode

def closestValueRecursive(root: treenode.TreeNode, target: float) -> int:
    def inorder(r: treenode.TreeNode):
        return inorder(r.left) + [r.val] + inorder(r.right) if r else []
    
    return min(inorder(root), key = lambda x: abs(target - x))