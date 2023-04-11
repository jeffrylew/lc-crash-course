import treenode

def diameterOfBinaryTree(root: treenode.TreeNode) -> int:
    diameter = 0

    def longest_path(node):
        if not node:
            return 0
        
        nonlocal diameter

        # Recursively find longest path in both left child and right child
        left_path = longest_path(node.left)
        right_path = longest_path(node.right)

        # Update diameter if left_path plus right_path is larger
        diameter = max(diameter, left_path + right_path)

        # Return longer between left_path and right_path
        # Remember to add 1 for path connecting node and its parent
        return max(left_path, right_path) + 1
    
    longest_path(root)
    return diameter