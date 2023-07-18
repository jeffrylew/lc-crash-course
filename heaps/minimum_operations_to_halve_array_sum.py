from heapq import *


def halveArray(nums: list[int]) -> int:
    target = sum(nums) / 2
    heap = [-num for num in nums]
    heapify(heap)

    ans = 0
    while target > 0:
        ans += 1
        x = heappop(heap)
        target += x / 2
        heappush(heap, x / 2)
    
    return ans