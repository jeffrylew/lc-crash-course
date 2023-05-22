from collections import defaultdict

def minReorder(n: int, connections: list[list[int]]) -> int:
    roads = set()
    graph = defaultdict(list)

    for x, y in connections:
        graph[x].append(y)
        graph[y].append(x)
        roads.add((x, y))
    
    def dfsRecursive(node):
        ans = 0
        for neighbor in graph[node]:
            if neighbor not in seen:
                if (node, neighbor) in roads:
                    ans += 1
                
                seen.add(neighbor)
                ans += dfsRecursive(neighbor)

        return ans
    
    def dfsIterative(start):
        ans = 0
        stack = [start]
        while stack:
            node = stack.pop()
            for neighbor in graph[node]:
                if neighbor not in seen:
                    if (node, neighbor) in roads:
                        ans += 1
                    seen.add(neighbor)
                    stack.append(neighbor)
        
        return ans
    
    seen = {0}
    return dfsRecursive(0)
    # return dfsIterative(0)