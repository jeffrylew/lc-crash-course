from heapq import *


def findMaximizedCapital(
    k: int, w: int, profits: list[int], capital: list[int]
) -> int:
    n = len(profits)
    projects = sorted(zip(capital, profits))
    heap = []
    i = 0

    for _ in range(k):
        while i < n and projects[i][0] <= w:
            heappush(heap, -projects[i][1])
            i += 1
        
        if len(heap) == 0:
            # Not enough money to do any more projects
            return w
        
        # Minus because stored negative numbers on heap
        w -= heappop(heap)
    
    return w
