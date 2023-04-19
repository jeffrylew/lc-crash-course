import treenode

from collections import deque

def deepestLeavesSumDFS(root: treenode.TreeNode) -> int:
    deepest_sum = depth = 0
    stack = [(root, 0)]

    while stack:
        node, curr_depth = stack.pop()

        if node.left is None and node.right is None:
            # If this leaf is the deepest one seen so far
            if depth < curr_depth:
                # Start new sum
                deepest_sum = node.val

                # Note new depth
                depth = curr_depth
            elif depth == curr_depth:
                # If there were already leaves at this depth,
                # update existing sum
                deepest_sum += node.val
        else:
            if node.right:
                stack.append((node.right, curr_depth + 1))

            if node.left:
                stack.append((node.left, curr_depth + 1))
    
    return deepest_sum

def deepestLeavesSumBFS(root: treenode.TreeNode) -> int:
    next_level = deque([root,])

    while next_level:
        # Prepare for the next level
        curr_level = next_level
        next_level = deque()

        for node in curr_level:
            # Add child nodes of the current level
            # in the queue for the next level
            if node.left:
                next_level.append(node.left)
            
            if node.right:
                next_level.append(node.right)
        
    return sum([node.val for node in curr_level])
        