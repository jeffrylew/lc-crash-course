class Solution:
    def canVisitAllRooms(rooms: list[list[int]]) -> bool:
        def dfsRecursive(node):
            for neighbor in rooms[node]:
                if neighbor not in seen:
                    seen.add(neighbor)
                    dfsRecursive(neighbor)

        def dfsIterative(start):
            stack = [start]
            while stack:
                node = stack.pop()
                for neighbor in rooms[node]:
                    if neighbor not in seen:
                        seen.add(neighbor)
                        stack.append(neighbor)
        
        seen = {0}
        dfsRecursive(0)
        # dfsIterative(0)
        return len(seen) == len(rooms)