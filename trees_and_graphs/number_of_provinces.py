from collections import defaultdict

class Solution:
    def findCircleNum(self, isConnected: list[list[int]]) -> int:
        def dfsRecursive(node):
            for neighbor in graph[node]:
                # The next 2 lines are needed to prevent cycles
                if neighbor not in seen:
                    seen.add(neighbor)
                    dfsRecursive(neighbor)
        
        def dfsIterative(start):
            stack = [start]
            while stack:
                node = stack.pop()
                for neighbor in graph[node]:
                    if neighbor not in seen:
                        seen.add(neighbor)
                        stack.append(neighbor)
        
        # Build the graph
        n = len(isConnected)
        graph = defaultdict(list)
        for i in range(n):
            for j in range(i + 1, n):
                if isConnected[i][j]:
                    graph[i].append(j)
                    graph[j].append(i)
        
        seen = set()
        ans = 0

        for i in range(n):
            if i not in seen:
                # Add all nodes of a connected component to the set
                ans += 1
                seen.add(i)
                dfsRecursive(i)
                # dfsIterative(i)
        
        return ans