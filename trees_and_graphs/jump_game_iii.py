from collections import deque

def canReachBFS(arr: list[int], start: int) -> bool:
    n = len(arr)
    queue = deque([start])

    while queue:
        node = queue.popleft()

        # Check if reached zero
        if arr[node] == 0:
            return True
        
        if arr[node] < 0:
            continue

        # Check available next steps
        for i in [node + arr[node], node - arr[node]]:
            if 0 <= i < n:
                queue.append(i)
        
        # Mark as visited
        arr[node] = -arr[node]
    
    return False