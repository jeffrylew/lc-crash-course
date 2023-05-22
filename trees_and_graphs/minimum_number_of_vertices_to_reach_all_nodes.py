def findSmallestSetOfVertices(n: int, edges: list[list[int]]) -> list[int]:
    indegree = [0] * n
    for _, y in edges:
        indegree[y] += 1
    
    return [node for node in range(n) if indegree[node] == 0]