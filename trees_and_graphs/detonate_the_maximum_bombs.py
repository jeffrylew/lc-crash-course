from collections import defaultdict
from collections import deque

def maximumDetonationDFS(bombs: list[list[int]]) -> int:
    graph = defaultdict(list)
    n = len(bombs)

    # Build the graph
    for i in range(n):
        for j in range(i + 1, n):
            xi, yi, ri = bombs[i]
            xj, yj, rj = bombs[j]

            dx2 = (xi - xj) ** 2
            dy2 = (yi - yj) ** 2
            ri2, rj2 = ri ** 2, rj **2

            # Create a path from node i to node j if bomb i detonates bomb j
            if ri2 >= dx2 + dy2:
                graph[i].append(j)
            
            # Create a path from node j to node i if bomb j detonates bomb i
            if rj2 >= dx2 + dy2:
                graph[j].append(i)
    
    # DFS to get the number of nodes reachable from a given node
    def dfsRecursive(curr_node, visited):
        visited.add(curr_node)

        for neighbor in graph[curr_node]:
            if neighbor not in visited:
                dfsRecursive(neighbor, visited)
        
        return len(visited)
    
    def dfsIterative(curr_node):
        stack = [curr_node]
        visited2 = set([curr_node])

        while stack:
            node = stack.pop()

            for neighbor in graph[node]:
                if neighbor not in visited2:
                    visited2.add(neighbor)
                    stack.append(neighbor)
        
        return len(visited2)
    
    # BFS to get the number of nodes reachable from a given node
    def bfs(curr_node):
        queue = deque([curr_node])
        visited3 = set([curr_node])

        while queue:
            node = queue.popleft()

            for neighbor in graph[node]:
                if neighbor not in visited3:
                    visited3.add(neighbor)
                    queue.append(neighbor)
        
        return len(visited3)
    
    ans = 0
    for i in range(n):
        # visited = set()
        # ans = max(ans, dfsRecursive(i, visited))

        # ans = max(ans, dfsIterative(i))

        ans = max(ans, bfs(i))
    
    return ans