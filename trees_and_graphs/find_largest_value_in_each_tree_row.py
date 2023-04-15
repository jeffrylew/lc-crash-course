import treenode
from collections import deque

def largestValues(root: treenode.TreeNode) -> List[int]:
    if not root:
        return []
    
    ans = []
    queue = deque([root])

    while queue:
        current_length = len(queue)

        # This will store the largest value for the current level
        curr_max = float("-inf")

        for _ in range(current_length):
            node = queue.popleft()
            curr_max = max(curr_max, node.val)

            if node.left:
                queue.append(node.left)

            if node.right:
                queue.append(node.right)
        
        ans.append(curr_max)
    
    return ans