from heapq import *


def findKthLargestDS1(nums: list[int], k: int) -> int:
    nums.sort(reverse=True)
    return nums[k - 1]


def findKthLargestDS2(nums: list[int], k: int) -> int:
    min_heap = []
    for num in nums:
        heappush(min_heap, num)

        if len(min_heap) > k:
            heappop(min_heap)
    
    return min_heap[0]