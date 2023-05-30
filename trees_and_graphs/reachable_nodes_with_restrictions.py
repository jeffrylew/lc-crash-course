from collections import defaultdict
from collections import deque

def reachableNodesBFS(
    n: int,
    edges: list[list[int]],
    restricted: list[int]
) -> int:
    # Store all edges in neighbors
    neighbors = defaultdict(list)
    for node_a, node_b in edges:
        neighbors[node_a].append(node_b)
        neighbors[node_b].append(node_a)
    
    # Mark the nodes in restricted as visited
    seen = [False] * n
    for node in restricted:
        seen[node] = True
    
    # Store all nodes to be visited in queue
    ans = 0
    queue = deque([0])
    seen[0] = True

    while queue:
        curr_node = queue.popleft()
        ans += 1

        for next_node in neighbors[curr_node]:
            if not seen[next_node]:
                seen[next_node] = True
                queue.append(next_node)
    
    return ans

def reachableNodeDFSRecursive(
    n: int,
    edges: list[list[int]],
    restricted: list[int]
) -> int:
    neighbors = defaultdict(list)
    for node_a, node_b in edges:
        neighbors[node_a].append(node_b)
        neighbors[node_b].append(node_a)
    
    seen = [False] * n
    for node in restricted:
        seen[node] = True

    def dfsRecursive(curr_node):
        nonlocal ans
        ans += 1

        seen[curr_node] = True

        for next_node in neighbors[curr_node]:
            if not seen[next_node]:
                dfsRecursive(next_node)
    
    ans = 0
    dfsRecursive(0)
    return ans