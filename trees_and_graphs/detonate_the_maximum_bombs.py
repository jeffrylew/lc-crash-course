from collections import defaultdict

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
    
    ans = 0
    for i in range(n):
        visited = set()
        ans = max(ans, dfsRecursive(i, visited))
    
    return ans