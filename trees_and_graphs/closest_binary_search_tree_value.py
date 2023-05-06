import treenode

def closestValueRecursive(root: treenode.TreeNode, target: float) -> int:
    def inorder(r: treenode.TreeNode):
        return inorder(r.left) + [r.val] + inorder(r.right) if r else []
    
    return min(inorder(root), key = lambda x: abs(target - x))


def closestValueIterative(root: treenode.TreeNode, target: float) -> int:
    stack, pred = [], float('-inf')

    while stack or root:
        while root:
            stack.append(root)
            root = root.left
        root = stack.pop()

        if pred <= target and target < root.val:
            return min(pred, root.val, key = lambda x: abs(target - x))
        
        pred = root.val
        root = root.right
    
    return pred