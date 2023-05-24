from collections import defaultdict

def validPath(n: int, edges: list[list[int]], source: int, destination: int
)-> bool:
    # Store all edges in 'graph'
    graph = defaultdict(list)
    for a, b in edges:
        graph[a].append(b)
        graph[b].append(a)

    seen = [False] * n
    
    def dfsRecursive(curr_node):
        if curr_node == destination:
            return True
        if not seen[curr_node]:
            seen[curr_node] = True
            for next_node in graph[curr_node]:
                if dfsRecursive(next_node):
                    return True
        return False
    
    return dfsRecursive(source)