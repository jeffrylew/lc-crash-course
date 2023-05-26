from collections import defaultdict

def countComponents(n: int, edges: list[list[int]]) -> int:
    def dfsRecursive(start):
        visited[start] = True

        for neighbor in graph[start]:
            if not visited[neighbor]:
                dfsRecursive(neighbor)

    if n == 0:
        return 0

    components = 0
    visited = [False] * n
    graph = defaultdict(list)

    for x, y in edges:
        graph[x].append(y)
        graph[y].append(x)
    
    for node in range(n):
        if not visited[node]:
            components += 1
            dfsRecursive(node)
    
    return components
