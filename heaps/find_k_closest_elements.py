from heapq import *


def findClosestElementsDS1(arr: list[int], k: int, x: int) -> list[int]:
    max_heap = []

    for num in arr:
        distance = abs(x - num)
        heappush(max_heap, (-distance, -num))

        if len(max_heap) > k:
            heappop(max_heap)
    
    return sorted([-pair[1] for pair in max_heap])
