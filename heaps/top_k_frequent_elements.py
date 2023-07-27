from collections import Counter
from heapq import *

def topKFrequent(nums: list[int], k: int) -> list[int]:
    counts = Counter(nums)
    min_heap = []

    for num, count in counts.items():
        heappush(min_heap, (count, num))

        if len(min_heap) > k:
            heappop(min_heap)
    
    return [pair[1] for pair in min_heap]