from collections import deque

def print_all_nodes(root):
    queue = deque([root])
    while queue:
        nodes_in_current_level = len(queue)

        # Do some logic here for the current level

        for _ in range(nodes_in_current_level):
            node = queue.popleft()

            # Do some logic here on the current node
            print(node.val)

            # Put the next level onto the queue
            if node.left:
                queue.append(node.left)

            if node.right:
                queue.append(node.right)