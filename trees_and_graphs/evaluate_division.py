from collections import defaultdict

def calcEquation(
    equations: list[list[str]], values: list[float], queries: list[list[str]]
) -> list[float]:
    def answer_query(start, end):
        # no info on this node
        if start not in graph:
            return -1
        
        seen = {start}
        stack = [(start, 1)]

        while stack:
            node, ratio = stack.pop()
            if node == end:
                return ratio
            
            for neighbor in graph[node]:
                if neighbor not in seen:
                    seen.add(neighbor)
                    stack.append((neighbor, ratio * graph[node][neighbor]))
        
        return -1
    
    graph = defaultdict(dict)

    for i in range(len(equations)):
        numerator, denominator = equations[i]
        val = values[i]

        graph[numerator][denominator] = val
        graph[denominator][numerator] = 1 / val
    
    ans = []

    for numerator, denominator in queries:
        ans.append(answer_query(numerator, denominator))
    
    return ans