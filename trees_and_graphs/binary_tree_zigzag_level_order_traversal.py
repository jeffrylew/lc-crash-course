import treenode

from collections import deque

def zigzagLevelOrderBFS(root: treenode.TreeNode) -> list[list[int]]:
    """
    :type root: TreeNode
    :rtype: List[List[int]]
    """
    if root is None:
        return []
    
    results = []

    node_queue = deque([root, None])

    level_list = deque()
    is_order_left = True

    while node_queue:
        curr_node = node_queue.popleft()

        if curr_node:
            if is_order_left:
                level_list.append(curr_node.val)
            else:
                level_list.appendleft(curr_node.val)

            if curr_node.left:
                node_queue.append(curr_node.left)
            
            if curr_node.right:
                node_queue.append(curr_node.right)
        else:
            # We finish one level
            results.append(level_list)
            level_list = deque()

            # Add a delimiter to mark the level
            if node_queue:
                node_queue.append(None)
            
            is_order_left = not is_order_left

    return results
