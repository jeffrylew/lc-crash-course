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


def closestValueBinarySearch(root: treenode.TreeNode, target: float) -> int:
    closest = root.val
    while root:
        # Editorial is incorrect here. If have root 4 with right child 5 and
        # target is 4.5 then the following will set closest to 5 instead of 4
        # closest = min(root.val, closest, key = lambda x: abs(target - x))

        arg = (root.val, closest) if root.val < closest else (closest, root.val)
        closest = min(*arg, key = lambda x: abs(target - x))

        root = root.left if target < root.val else root.right
    return closest